/*
htdetect horizontal transfert detection tools
Copyright (C) 2011  Laurent Modolo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "BlastControler.hpp"

BlastControler::BlastControler(bool verbose) : BlastModel::BlastModel(verbose) {}
BlastControler::~BlastControler() {}

void BlastControler::sort()
{
	Blast_query.sort();
}

void BlastControler::remove_overlapping()
{
	if(Blast_verbose){ cout << "removing overlapping for " << Blast_query.size() << " hits." << endl; }
	Blast_query.sort();
	
	list<Hit*> tmp;
	ProgressBar progress(1, 4, 0, Blast_query.size(), Blast_verbose);
	
	for(int i = 0; i < Blast_query.size(); i++)
	{
		tmp.push_back(Blast_query.hit(i));
		if(Blast_verbose)
			progress.inc();
	}
	Blast_query.clear_nodelete();
	
	list<Hit*>::iterator it, it_next;
	
	it = tmp.begin();
	it_next = it;
	it_next++;
	
	progress(2, 0, tmp.size());
	
	while(it != tmp.end() && it_next != tmp.end())
	{
		if((*it)->over(**it_next))
		{
			if((*it)->sens() != (*it_next)->sens())
			{
				Blast_target.at((*it_next)->id())->flip_all();
			}
			
			(*it)->merge(**it_next);
			Blast_target.at((*it)->id())->merge(*Blast_target.at((*it_next)->id()));
			
			Blast_target.at((*it_next)->id())->clear_nodelete();
			delete Blast_target.at((*it_next)->id());
			Blast_target.at((*it_next)->id()) = nullptr;
			delete *it_next;
			*it_next = nullptr;
			
			it_next = tmp.erase(it_next);
		}
		else
		{
			it++;
			it_next++;
		}
		progress.inc();
	}
	
	progress(3, 0, tmp.size());
	
	list<Hit*>::iterator hit = tmp.begin();
	
	while(hit != tmp.end())
	{
		Blast_query.add_hit(*hit);
		*hit = nullptr;
		progress.inc();
		hit++;
	}
	
	progress(4, 0, Blast_target.size());
	
	for(int i = 0; i < Blast_target.size(); i++)
	{
		if(Blast_target.at(i) != nullptr)
			Blast_target.at(i)->remove_overlapping();
		
		progress.inc();
	}
	if(Blast_verbose){ cout << endl << "Hits number : " << size() << endl;}
}

void parallel_remove_overlapping()
{
	
}

void BlastControler::compute_identity(int thread_number, string tmp_rep)
{
	if(Blast_verbose){ cout << "Computing identity for " << Blast_identity.size() << " hits." << endl; }
	if(Blast_fasta_a != nullptr && Blast_fasta_b != nullptr)
	{
		int t_number;
		if(thread_number > size())
		{
			if(size() > 1)
				t_number = size()-1;
			else
				t_number = 1;
		}
		else
		{
			t_number = thread_number;
		}
		
		mThread<AlignementGet> alignements_run(t_number);
		
		ProgressBar progress(1, 1, 0, Blast_identity.size(), Blast_verbose);
		
		for(unsigned int i = 0; i < size(); i++)
		{
			for(unsigned int j = 0; j < hit_target_size(i); j++)
			{
				alignements_run.add(AlignementGet(Blast_fasta_a, &(*hit_query(i)), Blast_fasta_b, &(*hit_target(i, j)), &Blast_identity, &Blast_muscle_path, hit_target(i, j)->id(), &tmp_rep));
				
				progress.inc();
			}
		}
		alignements_run.stop();
	}
}

void BlastControler::compute_test(double chromosome_identity, int thread_number)
{
	if(Blast_verbose){ cout << "Computing p-value for " << Blast_pvalue.size() << " hits." << endl; }
	
	int t_number;
	if(thread_number > size())
	{
		if(size() > 1)
			t_number = size()-1;
		else
			t_number = 1;
	}
	else
	{
		t_number = thread_number;
	}
	
	mThread<pTest> alignements_run(t_number);
	
	ProgressBar progress(1, 1, 0, Blast_pvalue.size(), Blast_verbose);
	
	for(unsigned int i = 0; i < size(); i++)
	{
		for(unsigned int j = 0; j < hit_target_size(i); j++)
		{
			alignements_run.add(pTest(chromosome_identity, identity(i,j), hit_query(i)->size(), &(Blast_pvalue.at(hit_target(i,j)->id())), &(Blast_statistic.at(hit_target(i,j)->id()))));
			
			progress.inc();
		}
	}
	alignements_run.stop();
}

void BlastControler::remove_overlapping_2(double chromosome_identity, int thread_number)
{
	try
	{
		if(Blast_verbose){ cout << "removing overlapping for " << Blast_target.size() << " hits." << endl; }
	
		PathWalker paths(chromosome_identity, &Blast_identity, Blast_verbose);
		ProgressBar progress(1, 1, 0, Blast_pvalue.size(), Blast_verbose);
		
		for(unsigned int i = 0; i < size(); i++)
		{
			for(unsigned int j = 0; j < hit_target_size(i); j++)
			{
				paths.add(i, hit_query(i), hit_target(i,j));
				progress.inc();
			}
		}
		
		progress.clear();
		
		int t_number;
		if(thread_number > size())
		{
			if(size() > 1)
				t_number = size()-1;
			else
				t_number = 1;
		}
		else
		{
			t_number = thread_number;
		}
		
		paths.compute_pvalue(t_number);
		paths.rm_overlapping_Path(thread_number);
		paths.rm_overlapping_Path(thread_number);
		paths.rm_overlapping_Path(thread_number);
		vector<HitList*>* new_hitlist = paths.result();
		
		if(new_hitlist->size() != Blast_query.size())
			throw logic_error("target size liste error");
		
		for(int i = 0; i < Blast_target.size(); i++)
		{
			if(Blast_target.at(i) != nullptr)
			{
				Blast_target.at(i)->clear_nodelete();
				delete Blast_target.at(i); // there is many hit lost and undeleted
				Blast_target.at(i) = nullptr;
			}
		}
		Blast_target = *new_hitlist;
		
		for(int i = 0; i < Blast_target.size(); i++)
		{
			Blast_query.hit(i)->set_id(i);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void BlastControler::remove_overlapping_2(double chromosome_identity, int thread_number)" << endl;
	}
}

void BlastControler::neighbor()
{
	ProgressBar progress(1, 1, 0, Blast_identity.size(), Blast_verbose);
	
	for(int i = 1; i < size()-1; i++)
	{
		for(int j = 0; j < hit_target_size(i); j++)
		{
			for(int j_prev = 0; j_prev < hit_target_size(i-1); j_prev++)
			{
				if(hit_target(i-1, j_prev)->neighbor(*hit_target(i, j)))
					set_neighbor_prev(i, j, true);
			}
			for(int j_next = 0; j_next < hit_target_size(i+1); j_next++)
			{
				if(hit_target(i, j)->neighbor(*hit_target(i+1, j_next)))
					set_neighbor_next(i, j, true);
			}
			progress.inc();
		}
	}
}

