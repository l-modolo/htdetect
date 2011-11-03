#include "FastaControler.hpp"

FastaControler::FastaControler(string const & file) : FastaModel::FastaModel(file) {}

Sequence* FastaControler::findSeq(string const & header)
{
	auto it = std::find(Fasta_sequences.begin(), Fasta_sequences.end(), Sequence(header, 0, 10, 0));
	try{
		if(it == Fasta_sequences.end())
		{
			throw logic_error("Sequence not found : "+header+" in file "+Fasta_file);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in Sequence* FastaControler::findSeq(string const & header)" << endl;
	}
	return &(*it);
}

string FastaControler::find(string const & header)
{
	Sequence* s = findSeq(header);
	string seq;
	try
	{
		ifstream fFasta(Fasta_file);
		
		if(fFasta)
		{
			fFasta.seekg(s->start());
			char currentchar = fFasta.get();
			while(fFasta.tellg() < s->stop())
			{
				if(currentchar != '\n' && currentchar != '\r' && currentchar != EOF)
					seq.push_back(currentchar);
				currentchar = fFasta.get();
			}
			fFasta.close();
		}
		else
		{
			throw logic_error("Can not open file : "+Fasta_file);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in string FastaControler::find(string const & header)"<< endl;
	}
	return seq;
}

string FastaControler::find(string const & header, long long int start, long long int stop)
{
	Sequence* s = findSeq(header);
	string seq;
	if(s->stop() < s->pos(stop))
	{
		stop = s->stop();
	}
	else
	{
		stop = s->pos(stop);
	}
	
	try
	{
		ifstream fFasta(Fasta_file);
		
		if(fFasta)
		{
			fFasta.seekg(s->pos(start));
			char currentchar = fFasta.get();
			
			while(fFasta.tellg() < stop)
			{
				if(currentchar != '\n' && currentchar != '\r' && currentchar != EOF)
					seq.push_back(currentchar);
				currentchar = fFasta.get();
			}
			fFasta.close();
		}
		else
		{
			throw logic_error("Can not open file : "+Fasta_file);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in string FastaControler::find(string const & header, long long int start, long long int stop)" << endl;
	}
	return seq;
}

string FastaControler::find(string const & header, long long int start, long long int stop, bool reverse)
{
	string seq = find(header, start, stop);
	if(reverse)
	{
		std::reverse(seq.begin(),seq.end());
	}
	return seq;
}
