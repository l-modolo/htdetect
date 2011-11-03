#ifndef DEF_BlastView
#define DEF_BlastView
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "BlastControler.hpp"

using namespace std;

class Blast : public BlastControler
{
	public:
	Blast();
	Blast(string const & name, string const & file);
	Blast(string const & name, string const & file, Fasta* fasta);
	Blast(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2);
	Blast(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2, string const & muscle_path);
	~Blast();
	
	static int number();
	
	protected:
	static int Blast_number;
	void display(ostream &stream);
	
	friend std::ostream& operator<< (std::ostream& flux, Blast &hitbis);
};

#endif

