#include "Fasta.hpp"

Fasta::Fasta(string const & file) : FastaControler::FastaControler(file) {}

void Fasta::display(ostream &stream) const
{
	stream << Fasta_file << endl;
	for(auto &s : Fasta_sequences)
	{
		stream << s << endl;
	}
}

ostream &operator<<( ostream &stream, Fasta const& f)
{
	f.display(stream);
	return stream;
}
