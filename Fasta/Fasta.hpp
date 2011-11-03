#ifndef DEF_Fasta
#define DEF_Fasta

#include "FastaControler.hpp"

using namespace std;

class FastaThread;

class Fasta : public FastaControler
{
	public:
	Fasta(string const & file);
	
	private:
	void display(ostream &stream) const;
	
	friend std::ostream& operator<< (std::ostream& flux, Fasta const& Fastabis);
	friend class FastaThread;
};

#endif
