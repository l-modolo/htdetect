#ifndef DEF_BlastControler
#define DEF_BlastControler
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <mutex>
#include <boost/math/distributions/poisson.hpp>
#include <boost/math/special_functions/round.hpp>
#include "BlastModel.hpp"
#include "../Alignement/Alignement.hpp"

using namespace std;

class BlastControler : public BlastModel
{
	public:
	BlastControler();
	BlastControler(string const & name, string const & file);
	BlastControler(string const & name, string const & file, string const & muscle_path);
	BlastControler(string const & name, string const & file, Fasta* fasta1);
	BlastControler(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2);
	BlastControler(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2, string const & muscle_path);
	
	
	void sort();
	void neighbor();
	void remove_overlapping();
	void compute_identity(int thread_number, string tmp_rep);
	void compute_test(double chromosome_identity, int thread_number);
	
	private:
	void parallel_compute_identity(unsigned int i, unsigned int j, string* tmp_rep, list<thread>* locks, int thread_number);
	
	void parallel_remove_overlapping();
	void parallel_compute_test(double chromosome_identity, unsigned int i, unsigned int j, list< thread >* alignements_run, int thread_number);
	void hitTest(double chromosome_identity,  unsigned int i, unsigned int j);
	
};
#endif

