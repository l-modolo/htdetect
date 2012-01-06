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

#include "AlignementWrite.hpp"


AlignementWrite::AlignementWrite(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, string* first_seq, string* second_seq, string* muscle_path, int thread_id , string* tmp_rep, mutex* controler) : Alignement(fasta_a, hit_a, fasta_b, hit_b, muscle_path, thread_id , tmp_rep)
{
	Alignement_controler = controler;
//	Alignement_controler->lock();
	
	Alignement_first_seq = first_seq;
	Alignement_second_seq = second_seq;
	
	Alignement_init = true;
}

AlignementWrite& AlignementWrite::operator=(AlignementWrite const& alignementbis)
{
	try
	{
		if(this != &alignementbis)
		{
			Alignement_controler = alignementbis.Alignement_controler;
			
			if(alignementbis.Alignement_first_seq == nullptr)
				throw logic_error("Alignement_first_seq copy of a nullptr pointer");
			Alignement_second_seq = alignementbis.Alignement_first_seq;
			
			if(alignementbis.Alignement_first_seq == nullptr)
				throw logic_error("Alignement_first_seq copy of a nullptr pointer");
			Alignement_second_seq = alignementbis.Alignement_second_seq;
			
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
		cerr << "ERROR : " << e.what() << " in : AlignementWrite& AlignementWrite::operator=(AlignementWrite const& alignementbis)" << endl;
		cerr << "a" << alignementbis.Alignement_id << endl;
	}
	return *this;
}

void AlignementWrite::run()
{
	try
	{
		if(Alignement_init)
		{
			if(Alignement_first_seq == nullptr || Alignement_second_seq == nullptr)
			{
			}
			else
			{
				FastaThread seqa(*Alignement_fasta_a, *Alignement_hit_a);
				FastaThread seqb(*Alignement_fasta_b, *Alignement_hit_b);
				string* first = seqa.find();
				string* second = seqb.find();
				
				if(first == nullptr || second == nullptr)
					throw logic_error("No sequences returned by FastaThread");
				
				*Alignement_first_seq = *first;
				*Alignement_second_seq = *second;
				delete first;
				delete second;
				
				trunquate_sequence();
			}
			if(Alignement_controler != nullptr)
				Alignement_controler->unlock();
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void AlignementWrite::run()" << endl;
		exit(-1);
	}
}

void AlignementWrite::operator()()
{
	if(Alignement_init)
	{
		AlignementWrite::run();
	}
}

void AlignementWrite::trunquate_sequence()
{
	try
	{
		if(Alignement_first_seq->length() != Alignement_second_seq->length())
		{
			AlignementWrite::align();
		}
	
		int size = Alignement_first_seq->length();
		int diff = 0;
		int gap = 0;
		double result = 0.0;
	
	
		int front = 0;
		int back = Alignement_second_seq->size()-1;
		while(Alignement_second_seq->at(front) == '-')
		{
			front++;
		}
		while(Alignement_second_seq->at(back) == '-')
		{
			back--;
		}
		
		*Alignement_first_seq = Alignement_first_seq->substr(front, back-front+1);
		*Alignement_second_seq = Alignement_second_seq->substr(front, back-front+1);
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in double AlignementWrite::trunquate_sequence()" << endl;
		cerr << Alignement_id << endl;
		cerr << ">" << *Alignement_first_seq << endl;
		cerr << ">" << *Alignement_second_seq << endl;
	}
}
