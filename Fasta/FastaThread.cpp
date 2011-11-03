#include "FastaThread.hpp"

FastaThread::FastaThread(Fasta * fasta, Hit * hit)
{
	try
	{
		if(fasta != nullptr)
			FastaThread_fasta = fasta;
		else
			throw logic_error("fasta does not exist");
		if(hit != nullptr)
			FastaThread_hit = hit;
		else
			throw logic_error("hit does not exist");
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in FastaThread::FastaThread(Fasta * fasta, Hit * hit)" << endl;
		exit(-1);
	}
}

Sequence FastaThread::findSeq()
{
	auto it = std::find(FastaThread_fasta->Fasta_sequences.begin(), FastaThread_fasta->Fasta_sequences.end(), Sequence(FastaThread_hit->name(), 0, 10, 0));
	try{
		if(it == FastaThread_fasta->Fasta_sequences.end())
		{
			throw logic_error("Sequence not found : "+(FastaThread_hit->name())+" in file "+(FastaThread_fasta->Fasta_file));
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in Sequence* FastaThread::findSeq()" << endl;
		exit(-1);
	}
	return (*it);
}

string* FastaThread::operator()()
{
	return FastaThread::find();
}

string* FastaThread::find()
{
	Sequence s = FastaThread::findSeq();
	string* seq = new string();
	long long int stop;
	if(s.stop() < s.pos(FastaThread_hit->stop()))
	{
		stop = s.stop();
	}
	else
	{
		stop = s.pos(FastaThread_hit->stop());
	}
	
	try
	{
		ifstream fFasta(FastaThread_fasta->Fasta_file);
		
		if(fFasta)
		{
			fFasta.seekg(s.pos(FastaThread_hit->start()));
			char currentchar = fFasta.get();
			
			while(fFasta.tellg() < stop && currentchar != EOF)
			{
				if(currentchar != '\n' && currentchar != '\r')
					seq->push_back(currentchar);
				
				currentchar = fFasta.get();
			}
			fFasta.close();
		}
		else
		{
			throw logic_error("Can not open file : "+(FastaThread_fasta->Fasta_file));
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in string* FastaThread::find()" << endl;
	}
	
	if(!FastaThread_hit->sens())
	{
		std::reverse(seq->begin(),seq->end());
	}
	return seq;
}

