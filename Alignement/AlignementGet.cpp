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

#include "AlignementGet.hpp"

AlignementGet::AlignementGet(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, vector<pair<long int, long int>>* identity, string* muscle_path, int thread_id, string* tmp_rep) : Alignement(fasta_a, hit_a, fasta_b, hit_b, muscle_path, thread_id , tmp_rep)
{
	Alignement_identity = identity;
	Alignement_first_seq = nullptr;
	Alignement_second_seq = nullptr;
	
	Alignement_init = true;
}

AlignementGet& AlignementGet::operator=(AlignementGet const& alignementbis)
{
	try
	{
		if(this != &alignementbis)
		{
			if(!alignementbis.Alignement_init)
				throw logic_error("Alignement_init set to false");
			
			if(alignementbis.Alignement_identity == nullptr)
				throw logic_error("Alignement_identity copy of a nullptr pointer");
			Alignement_identity = alignementbis.Alignement_identity;
			
			Alignement_first_seq = nullptr;
			Alignement_second_seq = nullptr;
			
			if(alignementbis.Alignement_fasta_a == nullptr)
				throw logic_error("Alignement_fasta_a copy of a nullptr pointer");
			Alignement_fasta_a = alignementbis.Alignement_fasta_a;
			
			if(alignementbis.Alignement_fasta_b == nullptr)
				throw logic_error("Alignement_fasta_b copy of a nullptr pointer");
			Alignement_fasta_b = alignementbis.Alignement_fasta_b;
			
			if(alignementbis.Alignement_hit_a == nullptr)
				throw logic_error("Alignement_hit_a copy of a nullptr pointer");
			Alignement_hit_a = alignementbis.Alignement_hit_a;
			
			if(alignementbis.Alignement_hit_b == nullptr)
				throw logic_error("Alignement_hit_b copy of a nullptr pointer");
			Alignement_hit_b = alignementbis.Alignement_hit_b;
			
			
			if(alignementbis.Alignement_path == nullptr)
				throw logic_error("Alignement_path copy of a nullptr pointer");
			Alignement_path = alignementbis.Alignement_path;
			
			if(alignementbis.Alignement_tmp_rep == nullptr)
				throw logic_error("Alignement_tmp_rep copy of a nullptr pointer");
			Alignement_tmp_rep = alignementbis.Alignement_tmp_rep;
			
			if( alignementbis.Alignement_id < 0)
				throw logic_error("thread id must be a positive integer");
			Alignement_id = alignementbis.Alignement_id;
			
			Alignement_init = true;
		}
		else
		{
			throw logic_error("copy of this");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : AlignementGet& AlignementGet::operator=(AlignementGet const& alignementbis)" << endl;
		cerr << "a" << alignementbis.Alignement_id << endl;
	}
	return *this;
}

void AlignementGet::run()
{
	try
	{
		if(Alignement_init)
		{
			if( (Alignement_identity->at(Alignement_hit_b->id())).first == -1)
			{
				FastaThread seqa(*Alignement_fasta_a, *Alignement_hit_a);
				FastaThread seqb(*Alignement_fasta_b, *Alignement_hit_b);
				
				Alignement_first_seq = seqa.find();
				Alignement_second_seq = seqb.find();
				
				pair<long int, long int> identity = compute_identity(false);
				
				if((Alignement_first_seq->length() - identity.second) > 0)
				{
					if( (identity.first/(Alignement_first_seq->length() - identity.second)) >= 0.5)
					{
						delete Alignement_first_seq;
						delete Alignement_second_seq;
						Alignement_first_seq = seqa.find();
						Alignement_second_seq = seqb.find();
						Alignement_identity->at(Alignement_hit_b->id()) = compute_identity(true);
					}
					if( (Alignement_identity->at(Alignement_hit_b->id())).first > identity.first || (Alignement_identity->at(Alignement_hit_b->id())).first == -1)
					{
						Alignement_identity->at(Alignement_hit_b->id()) = identity;
					}
				}
				delete Alignement_first_seq;
				delete Alignement_second_seq;
			}
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void AlignementGet::run()" << endl;
		exit(-1);
	}
}

void AlignementGet::operator()()
{
	if(Alignement_init)
	{
		AlignementGet::run();
	}
}

void AlignementGet::operator()(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, vector<pair<long int, long int>>* identity, string* muscle_path, int thread_id, string* tmp_rep)
{
	Alignement_fasta_a = fasta_a;
	Alignement_fasta_b = fasta_b;
	Alignement_hit_a = hit_a;
	Alignement_hit_b = hit_b;
	
	Alignement_path = muscle_path;
	Alignement_tmp_rep = tmp_rep;
	
	Alignement_id = thread_id;
	Alignement_identity = identity;
	
	AlignementGet::run();
}

pair<long int, long int> AlignementGet::compute_identity(bool reverse)
{
	if(reverse)
	{
		complementary(Alignement_second_seq);
	}
	if(Alignement_first_seq->length() != Alignement_second_seq->length())
	{
		AlignementGet::align();
	}
	
	int size = Alignement_first_seq->length();
	int diff = 0;
	int gap = 0;
	pair<long int, long int> result (-1, -1);
	
	try
	{
		for(int i = 0 ; i < size ; i++)
		{
			if(tolower(Alignement_first_seq->at(i)) == 'n' || tolower(Alignement_second_seq->at(i)) == 'n' || Alignement_first_seq->at(i) == '-' || Alignement_second_seq->at(i) == '-')
			{
				gap++;
			}
			else
			{
				if(tolower(Alignement_first_seq->at(i)) != tolower(Alignement_second_seq->at(i))){
					diff++;
				}
			}
		}
		
		result.first = diff;
		result.second = gap;
		
		if(size - gap < 0)
		{
			cerr << *Alignement_first_seq << endl;
			cerr << *Alignement_second_seq << endl;
		}
	}
	catch(exception const& e)
	{
		cerr << endl;
		cerr << "ERROR : " << e.what() << " in double AlignementGet::identity()" << endl;
		cerr << *Alignement_hit_a << "\t" << *Alignement_hit_b << endl;
//		cerr << *Alignement_first_seq << endl;
//		cerr << *Alignement_second_seq << endl;
	}
	
	return result;
}
