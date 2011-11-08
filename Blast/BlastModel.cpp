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

#include "BlastModel.hpp"

BlastModel::BlastModel(bool verbose)
{
	Blast_verbose = verbose;
}

void BlastModel::load(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2)
{
	Blast_fasta_a = fasta1;
	Blast_fasta_b = fasta2;
	Blast_muscle_path = "/usr/bin/muscle";
	Blast_file = file;
	Blast_name = name;
	read();
}

BlastModel::BlastModel(BlastModel & Blastbis)
{
	Blast_fasta_a = Blastbis.Blast_fasta_a;
	Blast_fasta_b = Blastbis.Blast_fasta_b;
	Blast_muscle_path = Blastbis.Blast_muscle_path;
	Blast_file = Blastbis.Blast_file;
	Blast_name = Blastbis.Blast_name;
	Blast_verbose = Blastbis.Blast_verbose;
	
	Blast_query = Blastbis.Blast_query;
	Blast_target = Blastbis.Blast_target;
	
	for(auto & it : Blastbis.Blast_target)
	{
		it = nullptr;
	}
	
	Blast_neighbor_prev = Blastbis.Blast_neighbor_prev;
	Blast_neighbor_next = Blastbis.Blast_neighbor_next;
	Blast_identity = Blastbis.Blast_identity;
	Blast_pvalue = Blastbis.Blast_pvalue;
}

BlastModel::~BlastModel()
{
	for(auto & it : Blast_target)
	{
		if(it != nullptr)
			delete it;
	}
}

string BlastModel::name() const
{
	return Blast_name;
}

string BlastModel::file() const
{
	return Blast_file;
}

int BlastModel::size() const
{
	return Blast_query.size();
}

Hit* BlastModel::hit_query(int i)
{
	return Blast_query.hit(i);
}

Hit* BlastModel::hit_target(int i)
{
	try
	{
		if(Blast_target.at(hit_query(i)->id()) != nullptr && Blast_target.at(hit_query(i)->id())->size() != 0)
			return Blast_target.at(hit_query(i)->id())->hit(0);
		else
			throw logic_error("Blast_target is empty");
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : Hit* BlastModel::hit_target(int i)" << endl;
		return nullptr;
	}
}

Hit* BlastModel::hit_target(int i, int j)
{
	try
	{
		if(Blast_target.at(hit_query(i)->id()) != nullptr && Blast_target.at(hit_query(i)->id())->size() != 0)
			return Blast_target.at(hit_query(i)->id())->hit(j);
		else
			throw logic_error("Blast_target is empty");
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : Hit* BlastModel::hit_target(int i, int j)" << endl;
		return nullptr;
	}
}

int BlastModel::hit_target_size(int i)
{
	try
	{
		if(Blast_target.at(hit_query(i)->id()) != nullptr)
			return Blast_target.at(hit_query(i)->id())->size();
		else
			throw logic_error("Blast_target is empty");
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : int BlastModel::hit_target_size(int i)" << endl;
	}
	return 0;
}

HitList* BlastModel::target(int i)
{
	try
	{
		if(Blast_target.at(hit_query(i)->id()) != nullptr && Blast_target.at(hit_query(i)->id())->size() != 0)
			return Blast_target.at(hit_query(i)->id());
		else
			throw logic_error("Blast_target is empty");
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : HitList* BlastModel::target(int i)" << endl;
	}
	return nullptr;
}

double BlastModel::identity(int i, int j)
{
	try
	{
		return Blast_identity.at(hit_target(i,j)->id());
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : double BlastModel::identity(int i)" << endl;
		return 0.0;
	}
}

double BlastModel::pvalue(int i, int j)
{
	try
	{
		return Blast_pvalue.at(hit_target(i,j)->id());
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : double BlastModel::pvalue(int i, int j)" << endl;
		return 0.0;
	}
}

bool BlastModel::neighbor_prev(int i, int j)
{
	try
	{
		return Blast_neighbor_prev.at(hit_target(i,j)->id());
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : bool BlastModel::neighbor_prev(int i, int j)" << endl;
		return false;
	}
}

bool BlastModel::neighbor_next(int i, int j)
{
	try
	{
		return Blast_neighbor_next.at(hit_target(i,j)->id());
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : bool BlastModel::neighbor_next(int i, int j)" << endl;
		return false;
	}
}


void BlastModel::set_pvalue(int i, int j, double value)
{
	try
	{
		Blast_pvalue.at(hit_target(i,j)->id()) = value;
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : double BlastModel::pvalue(int i, int j)" << endl;
	}
}

void BlastModel::set_neighbor_prev(int i, int j, bool value)
{
	try
	{
		Blast_neighbor_prev.at(hit_target(i,j)->id()) = value;
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void BlastModel::set_neighbor_prev(int i, int j, bool value)" << endl;
	}
}

void BlastModel::set_neighbor_next(int i, int j, bool value)
{
	try
	{
		Blast_neighbor_next.at(hit_target(i,j)->id()) = value;
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void BlastModel::set_neighbor_prev(int i, int j, bool value)" << endl;
	}
}

void BlastModel::read()
{
	try
	{
		ifstream fBlast(Blast_file);
		int column_number;
		int column_start;
		
		int start;
		int stop;
		int qstart;
		int qstop;
		bool test;
		
		/*                      Reading the Blast file                        */
		if(fBlast)
		{
			// for each line of the Blast file
			string line;
			while(getline(fBlast, line))
			{
				column_number = 0;
				column_start = 0;
				
				start = -1;
				stop = -1;
				qstart = -1;
				qstop = -1;
				string name;
				string qname;
				size_t found1;
				size_t found2;
				
				for(int i = 0; i < line.length(); i++)
				{
					if(isspace((int)line[i]))
					{
						string sub (line.begin()+column_start, line.begin()+i);
						
						switch(column_number)
						{
							case 0:
								qname = sub.substr((size_t)0, sub.find_first_of(' '));
							break;
							case 1:
								name = sub.substr((size_t)1, sub.find_first_of(' '));
							break;
							case 6:
								qstart = atoi(sub.c_str());
							break;
							case 7:
								qstop = atoi(sub.c_str());
							break;
							case 8:
								start = atoi(sub.c_str());
							break;
							case 9:
								stop = atoi(sub.c_str());
							break;
						}
						column_number++;
						column_start = i;
					}
				}
				
				if(start != -1 && stop != -1 && qstart != -1 && qstop != -1)
				{
					Blast_query.add_hit(name, start, stop);
					
					Blast_target.push_back(new HitList());
					Blast_target.back()->add_hit(Blast_query.last_hit()->id(), qname, qstart, qstop);
				}
			}
			
			Blast_identity = vector<double>(Blast_query.size(), -1.0);
			Blast_neighbor_prev = vector<bool>(Blast_query.size(), false);
			Blast_neighbor_next = vector<bool>(Blast_query.size(), false);
			Blast_pvalue = vector<double>(Blast_query.size(), -1.0);
			
			fBlast.close();
		}
		else
		{
			throw logic_error("Can not open file : "+Blast_file);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what()  << " in : void BlastModel::read()" << endl;
	}
}

void BlastModel::sav()
{
	ofstream outputf(Blast_name+".sav");
	try
	{
		if(outputf)
		{
			outputf << Blast_name << endl;
			outputf << Blast_file << endl;
			outputf << Blast_muscle_path << endl;
			
			ProgressBar progress(1, 1, 0, size(), Blast_verbose);
			
			for(int i = 0; i < size(); i++)
			{
				for(int j = 0; j < hit_target_size(i); j++)
				{
					outputf << *hit_query(i);
					outputf << "\t" << *hit_target(i, j);
					outputf << "\t" << identity(i, j);
					outputf << "\t" << pvalue(i, j) << endl;
				}
				progress.inc();
			}
		}
		else
		{
			throw logic_error("Can not open "+Blast_name+".sav");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << endl;
	}
	outputf.close();
}

void BlastModel::restore(string const & file, Fasta* fasta_a, Fasta* fasta_b)
{
	try
	{
		Blast_fasta_a = fasta_a;
		Blast_fasta_b = fasta_b;
		
		ifstream fBlast(file);
		int column_number;
		int column_start;
		
		int tmp;
		int start;
		int stop;
		int qstart;
		int qstop;
		double identity;
		double pvalue;
		bool sens;
		
		Hit prev_hit;
		
		bool test;
		
		/*                      Reading the Blast file                        */
		if(fBlast)
		{
			// for each line of the Blast file
			string line;
			getline(fBlast, Blast_name);
			getline(fBlast, Blast_file);
			getline(fBlast, Blast_muscle_path);
			
			while(getline(fBlast, line))
			{
				column_number = 0;
				column_start = 0;
				
				start = -1;
				stop = -1;
				qstart = -1;
				qstop = -1;
				string name;
				string qname;
				size_t found1;
				size_t found2;
				
				for(int i = 0; i < line.length(); i++)
				{
					if(isspace((int)line[i]))
					{
						string sub (line.begin()+column_start, line.begin()+i);
						
						switch(column_number)
						{
							case 0:
								name = sub.substr((size_t)0, sub.find_first_of(' '));
							break;
							case 1:
								if(sub.c_str()[0] == '-')
									sens = false;
								else
									sens = true;
							break;
							case 2:
								start = atoi(sub.c_str());
							break;
							case 3:
								stop = atoi(sub.c_str());
								if(!sens)
								{
									tmp = start;
									start = stop;
									stop = tmp;
								}
							break;
							case 5:
								qname = sub.substr((size_t)1, sub.find_first_of(' '));
							break;
							case 6:
								if(sub.c_str()[0] == '-')
									sens = false;
								else
									sens = true;
							break;
							case 7:
								qstart = atoi(sub.c_str());
							break;
							case 8:
								qstop = atoi(sub.c_str());
								if(!sens)
								{
									tmp = qstart;
									qstart = qstop;
									qstop = tmp;
								}
							break;
							case 10:
								identity = atof(sub.c_str());
							break;
							case 11:
								pvalue = atof(sub.c_str());
							break;
						}
						column_number++;
						column_start = i;
					}
				}
				
				if(Blast_query.size() == 0)
				{
					if(prev_hit.sens() == (start < stop) && prev_hit.start() == start &&  prev_hit.stop() == stop && prev_hit.name().compare(name) == 0)
					{
					
					}
					else
					{
						Blast_query.add_hit(name, start, stop);
						prev_hit = Hit(name, start, stop);
					}
				}
				else
				{
					Blast_query.add_hit(name, start, stop);
					prev_hit = Hit(name, start, stop);
				}
				
				Blast_target.push_back(new HitList());
				Blast_target.back()->add_hit(Blast_query.last_hit()->id(), qname, qstart, qstop);
				Blast_identity.push_back(identity);
				Blast_pvalue.push_back(pvalue);
			}
			
			Blast_neighbor_prev = vector<bool>(Blast_query.size(), false);
			Blast_neighbor_next = vector<bool>(Blast_query.size(), false);
			
			fBlast.close();
		}
		else
		{
			throw logic_error("Can not open file : "+Blast_file);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what()  << " in : void BlastModel::read()" << endl;
	}
}

