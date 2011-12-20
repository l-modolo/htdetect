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
	if(Blast_verbose){ cout << "Writting sequences for " << Blast_target.size() << " hits." << endl;}
	
	if(Blast_fasta_a != nullptr && Blast_fasta_b != nullptr)
	{
		mThread<Alignement> alignements_run(thread_number);
		string* qseq;
		string* tseq;
		writeSeq waitting_line(output);
		
		ProgressBar progress(1, 1, 0, Blast_target.size(), Blast_verbose);
		
		for(unsigned int i = 0; i < size(); i++)
		{
			for(unsigned int j = 0; j < hit_target_size(i); j++)
			{
				qseq = new string;
				tseq = new string;
				alignements_run.add(Alignement(Blast_fasta_a, hit_query(i), Blast_fasta_b, hit_target(i, j), qseq, tseq, &Blast_muscle_path, hit_target(i, j)->id(), &tmp_rep));
				waitting_line.add(hit_query(i), qseq, hit_target(i, j), tseq);
				
				progress.inc();
			}
		}
		alignements_run.stop();
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

