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
	
	for(int i = 0; i < size(); i++)
	{
		for(int j = 0; j < hit_target_size(i); j++)
		{
			if(pvalue(i, j) < 1.0)
			{
				stream << *hit_query(i);
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

