#ifndef DEF_FastaModel
#define DEF_FastaModel

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include "Sequence.hpp"

using namespace std;

class FastaModel
{
	public:
	FastaModel(string const & file);
	
	protected:
	// attributes
	string Fasta_file;
	vector<Sequence> Fasta_sequences;
};

#endif
