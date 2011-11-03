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

Blast::Blast(){}

Blast::Blast(string const & name, string const & file) : BlastControler::BlastControler(name, file)
{
	Blast_number++;
}

Blast::Blast(string const & name, string const & file, Fasta* fasta) : BlastControler::BlastControler(name, file, fasta)
{
	Blast_number++;
}

Blast::Blast(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2) : BlastControler::BlastControler(name, file, fasta1, fasta2)
{
	Blast_number++;
}

Blast::Blast(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2, string const & muscle_path) : BlastControler::BlastControler(name, file, fasta1, fasta2, muscle_path)
{
	Blast_number++;
}

Blast::~Blast()
{
	Blast_number--;
}

void Blast::display(ostream &stream)
{
	ProgressBar progress(1, 1, 0, size());
	
	stream << "target\tsens\tstat\tstop\tsize\tdist_prev\tdist_next\tquery\tsens\tstart\tstop\tsize\tid\tpvalue" << endl;
	
	for(int i = 0; i < size(); i++)
	{
		for(int j = 0; j < hit_target_size(i); j++)
		{
			if(pvalue(i, j) < 1.0)
			{
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
				stream << "\t" << pvalue(i, j) << endl;
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

