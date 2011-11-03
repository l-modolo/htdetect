#include "AlignementControler.hpp"

AlignementControler::AlignementControler(string const & seqa, string const & seqb, int mismatch, int gap) : AlignementModel::AlignementModel(seqa, seqb, mismatch, gap) {}

void AlignementControler::align(int base_number)
{
	int size_difference = 0;
	size_t long_seq_pos = 0;
	size_t short_seq_pos = 0;
	string gap("N");
	
	string* long_seq = nullptr;
	string* short_seq = nullptr;
	
	if(Alignement_first_seq.length() >= Alignement_second_seq.length())
	{
		long_seq = &Alignement_first_seq;
		short_seq = &Alignement_second_seq;
	}
	else
	{
		long_seq = &Alignement_second_seq;
		short_seq = &Alignement_first_seq;
	}
	size_difference = long_seq->length()-short_seq->length();
	
	if(size_difference != 0)
	{
		while(long_seq_pos < long_seq->length() - base_number)
		{
			if(eq(long_seq, short_seq, long_seq_pos, short_seq_pos, base_number))
			{
				long_seq_pos++;
				short_seq_pos++;
			}
			else
			{
				if(size_difference > 0)
				{
					if(short_seq_pos < short_seq->length())
						short_seq->insert(short_seq_pos, gap);
					else
						short_seq->push_back('N');
					size_difference--;
				}
				else
				{
					long_seq_pos = long_seq->length();
				}
			}
		}
	}
}

bool AlignementControler::eq(string* long_seq, string* short_seq, size_t long_seq_pos, size_t short_seq_pos, size_t next) const
{
	try
	{
		if(long_seq_pos+next < long_seq->length() && short_seq_pos+next < short_seq->length())
		{
			size_t count = 0;
			for(size_t i = 0; i <= next; i++)
			{
				if(long_seq->at(long_seq_pos+i) != short_seq->at(short_seq_pos+i))
				{
					count++;
				}
			}
			if(count == next)
				return false;
			else
				return true;
		}
		else
		{
			throw logic_error("Out of range of one of the two strings");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << endl;
		return false;
	}
}

