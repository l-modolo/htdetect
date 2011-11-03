#ifndef DEF_AlignementControler
#define DEF_AlignementControler
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <functional>
#include "AlignementModel.hpp"

using namespace std;

class AlignementControler : public AlignementModel
{
	public:
	AlignementControler(string const & seqa, string const & seqb, int mismatch, int gap);
	
	void align(int base_number);
	
	private:
	bool eq(string* long_seq, string* short_seq, size_t long_seq_pos, size_t short_seq_pos, size_t next) const;
};
#endif

