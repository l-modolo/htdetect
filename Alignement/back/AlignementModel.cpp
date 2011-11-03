#include "AlignementModel.hpp"

AlignementModel::AlignementModel(string const & seqa, string const & seqb, int mismatch, int gap)
{
	Alignement_first_seq = seqa;
	Alignement_second_seq = seqb;
	Alignement_mismatch = mismatch;
	Alignement_gap = gap;
}

string AlignementModel::first_seq() const
{
	return Alignement_first_seq;
}

string AlignementModel::second_seq() const
{
	return Alignement_second_seq;
}

int AlignementModel::mismatch() const
{
	return Alignement_mismatch;
}

int AlignementModel::gap() const
{
	return Alignement_gap;
}
