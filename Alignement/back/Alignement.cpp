#include "Alignement.hpp"

int Alignement::Alignement_number = 0;

int Alignement::number()
{
	return Alignement_number;
}

Alignement::Alignement(string const & seqa, string const & seqb, int mismatch, int gap) : AlignementControler::AlignementControler(seqa, seqb, mismatch, gap)
{
	Alignement_number++;
}

Alignement::~Alignement()
{
	Alignement_number--;
}

void Alignement::display(ostream &stream)
{
	stream << Alignement_first_seq << endl;
	stream << Alignement_second_seq << endl;
}

ostream &operator<<( ostream &stream, Alignement &b)
{
	b.display(stream);
	return stream;
}

