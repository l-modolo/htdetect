#ifndef DEF_FastaThread
#define DEF_FastaThread

#include "../Hit/Hit.hpp"
#include "Fasta.hpp"

using namespace std;

class FastaThread
{
	public:
	FastaThread(Fasta * fasta, Hit * hit);
	string* find();
	string* operator()();
	
	private:
	Sequence findSeq();
	
	Fasta * FastaThread_fasta;
	Hit * FastaThread_hit;
};

#endif
