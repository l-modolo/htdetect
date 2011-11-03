#ifndef DEF_AlignementModel
#define DEF_AlignementModel
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <utility>
#include "../HitList/HitList.hpp"

using namespace std;

class AlignementModel
{
	public:
	AlignementModel(string const & seqa, string const & seqb, int mismatch, int gap);
	
	string first_seq() const;
	string second_seq() const;
	int mismatch() const;
	int gap() const;
	
	protected:
	string Alignement_first_seq;
	string Alignement_second_seq;
	int Alignement_mismatch;
	int Alignement_gap;
};

#endif

