#ifndef DEF_FastaControler
#define DEF_FastaControler

#include "FastaModel.hpp"

using namespace std;

class FastaControler : public FastaModel
{
	public:
	FastaControler(string const & file);
	
	string find(string const & header);
	string find(string const & header, long long int start, long long int stop);
	string find(string const & header, long long int start, long long int stop, bool reverse);
	
	private:
	Sequence* findSeq(string const & header);
};

#endif
