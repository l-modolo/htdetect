#ifndef DEF_AlignementView
#define DEF_AlignementView
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "AlignementControler.hpp"

using namespace std;

class Alignement : public AlignementControler
{
	public:
	Alignement(string const & seqa, string const & seqb, int mismatch, int gap);
	~Alignement();
	
	static int number();
	
	protected:
	static int Alignement_number;
	void display(ostream &stream);
	
	friend std::ostream& operator<< (std::ostream& flux, Alignement &hitbis);
};

#endif

