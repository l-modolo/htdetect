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

#include "Blast.hpp"

int Blast::Blast_number = 0;

int Blast::number()
{
	return Blast_number;
}

Blast::Blast(bool verbose) : BlastControler::BlastControler(verbose)
{
	Blast_number++;
}

Blast::~Blast()
{
	Blast_number--;
}

void Blast::toFasta(string output, int thread_number, string tmp_rep)
{
	if(Blast_verbose){ cout << "Writting sequences for " << size() << " hits." << endl;}
	
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
		mThread<AlignementWrite> alignements_run(t_number);
		writeSeq writing_run(output);
		
		string* qseq;
		string* tseq;
		mutex* controler;
		Hit* qhit;
		Hit* thit;
		
		ProgressBar progress(1, 1, 0, size(), Blast_verbose);
		
		for(unsigned int i = 0; i < size(); i++)
		{
			for(unsigned int j = 0; j < hit_target_size(i); j++)
			{
				qhit = hit_query(i);
				thit = hit_target(i, j);
				qseq = new string;
				tseq = new string;
				controler = new mutex;
				
				controler->lock();
				
//				cout << i << "/" << size() << " " << j << "/" << hit_target_size(i) << endl;
				
				alignements_run.add(AlignementWrite(Blast_fasta_a, qhit, Blast_fasta_b, thit, qseq, tseq, &Blast_muscle_path, thit->id(), &tmp_rep, controler));
				writing_run.add(qhit, qseq, thit, tseq, controler);
				
				progress.inc();
			}
		}
		alignements_run.stop();
		writing_run.stop();
	}
}

void Blast::display(ostream &stream)
{
	ProgressBar progress(1, 1, 0, size(), Blast_verbose);
	
	stream << "number\ttarget\ttsens\ttstart\ttstop\ttsize\tdist_prev\tdist_next\tquery\tqsens\tqstart\tqstop\tqsize\tid\tpvalue\tstatistic" << endl;
	
	for(int i = 0; i < size(); i++)
	{
		for(int j = 0; j < hit_target_size(i); j++)
		{
			if(pvalue(i, j) <= 1.0)
			{
				stream << i << "\t";
				stream << *hit_query(i);
				if(i > 1)
					stream << "\t" << hit_query(i)->dist_to(*hit_query(i-1));
				else
					stream << "\t" << 0;
				if(i < size()-1)
					stream << "\t" << hit_query(i)->dist_to(*hit_query(i+1));
				else
					stream << "\t" << 0;
				stream << "\t" << *hit_target(i, j);
				stream << "\t" << identity(i, j);
				stream << "\t" << pvalue(i, j);
				stream << "\t" << statistic(i, j) << endl;
			}
		}
		progress.inc();
	}
}

ostream &operator<<( ostream &stream, Blast &b)
{
	b.display(stream);
	return stream;
}

