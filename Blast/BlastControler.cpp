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

BlastControler::BlastControler(){}
BlastControler::BlastControler(string const & name, string const & file) : BlastModel::BlastModel(name, file) {}
BlastControler::BlastControler(string const & name, string const & file, string const & muscle_path) : BlastModel::BlastModel(name, file, muscle_path) {}
BlastControler::BlastControler(string const & name, string const & file, Fasta* fasta1) : BlastModel::BlastModel(name, file, fasta1) {}
BlastControler::BlastControler(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2) : BlastModel::BlastModel(name, file, fasta1, fasta2) {}
BlastControler::BlastControler(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2, string const & muscle_path) : BlastModel::BlastModel(name, file, fasta1, fasta2, muscle_path) {}

void BlastControler::sort()
{
	Blast_query.sort();
}

void BlastControler::remove_overlapping()
{
	cout << "removing overlapping for " << Blast_query.size() << " hits." << endl;
	Blast_query.sort();
	
	list<Hit*> tmp;
	ProgressBar progress(1, 4, 0, Blast_query.size());
	
	for(int i = 0; i < Blast_query.size(); i++)
	{
		tmp.push_back(Blast_query.hit(i));
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
	cout << "Hits number : " << size() << endl;
}

void parallel_remove_overlapping()
{
	
}

void BlastControler::compute_identity(int thread_number, string tmp_rep)
{
	cout << "Computing identity for " << Blast_identity.size() << " hits." << endl;
	if(Blast_fasta_a != nullptr && Blast_fasta_b != nullptr)
	{
		list< thread > alignements_run;
		
		ProgressBar progress(1, 2, 0, Blast_identity.size());
		
		for(unsigned int i = 0; i < size(); i++)
		{
			for(unsigned int j = 0; j < hit_target_size(i); j++)
			{
				BlastControler::parallel_compute_identity(i, j, &tmp_rep, &alignements_run, thread_number);
				progress.inc();
			}
		}
		
		auto t1 = alignements_run.begin();
		while(t1 != alignements_run.end())
		{
				(*t1).join();
				t1 = alignements_run.erase(t1);
		}
	}
}

void BlastControler::parallel_compute_identity(unsigned int i, unsigned int j, string* tmp_rep, list< thread >* alignements_run, int thread_number)
{
	if(identity(i, j) == -1.0)
	{
		bool launched = false;
		list< thread >::iterator t1;
		
		while(!launched)
		{
			if(alignements_run->size() < thread_number)
			{
			
				alignements_run->push_back( thread{Alignement(Blast_fasta_a, hit_query(i), Blast_fasta_b, hit_target(i, j), &Blast_identity, &Blast_muscle_path, hit_target(i, j)->id(), tmp_rep)} );
				launched = true;
			}
			else
			{
				t1 = alignements_run->begin();
				while(t1 != alignements_run->end())
				{
					if((*t1).joinable())
					{
						(*t1).join();
						t1 = alignements_run->erase(t1);
					}
					else
						t1++;
				}
			}
		}
	}
}

void BlastControler::neighbor()
{
	ProgressBar progress(1, 1, 0, Blast_identity.size());
	
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

void BlastControler::compute_test(double chromosome_identity, int thread_number)
{
	try
	{
		list< thread > alignements_run;
		
		ProgressBar progress(1, 2, 0, Blast_pvalue.size());
		
		for(unsigned int i = 0; i < size(); i++)
		{
			for(unsigned int j = 0; j < hit_target_size(i); j++)
			{
				BlastControler::parallel_compute_test(chromosome_identity, i, j, &alignements_run, thread_number);
				progress.inc();
			}
		}
		
		auto t1 = alignements_run.begin();
		while(t1 != alignements_run.end())
		{
				(*t1).join();
				t1 = alignements_run.erase(t1);
		}
		
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void BlastControler::compute_test(double chromosome_identity)" << endl;
	}
}

void BlastControler::parallel_compute_test(double chromosome_identity, unsigned int i, unsigned int j, list< thread >* alignements_run, int thread_number)
{
	bool launched = false;
	list< thread >::iterator t1;
	
	while(!launched)
	{
		if(alignements_run->size() < thread_number)
		{
		
			alignements_run->push_back( thread{&BlastControler::hitTest, this, chromosome_identity, i, j} );
			launched = true;
		}
		else
		{
			t1 = alignements_run->begin();
			while(t1 != alignements_run->end())
			{
				if((*t1).joinable())
				{
					(*t1).join();
					t1 = alignements_run->erase(t1);
				}
				else
					t1++;
			}
		}
	}
}

void BlastControler::hitTest(double chromosome_identity,  unsigned int i, unsigned int j)
{
	double x;
	double T;
	double r = 1.0-(chromosome_identity/100.0);;
	
	if(identity(i,j) > chromosome_identity)
	{
		x = round((1.0-(identity(i,j)/100.0))*hit_target(i,j)->size());
		T = hit_target(i, j)->size();
	
		boost::math::poisson_distribution<> poisson(r*T);
		set_pvalue(i, j ,boost::math::cdf(poisson, x));
	}
	else
	{
		set_pvalue(i, j ,1);
	}
}

