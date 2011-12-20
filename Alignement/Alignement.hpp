/*
htdetect horizontal transfert detection tools
Copyright (C) 2011  Laurent Modolo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DEF_Alignement
#define DEF_Alignement

#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <future>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../Fasta/FastaThread.hpp"

using namespace std;

class Alignement {
	public:
	Alignement(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, vector<double>* identity, string* muscle_path, int thread_id , string* tmp_rep);
	Alignement(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, string* first_seq, string* second_seq, string* muscle_path, int thread_id , string* tmp_rep);
	
	Alignement& operator=(Alignement const& alignementbis);
	
	void operator()();
	void operator()(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, vector<double>* identity, string* muscle_path, int thread_id, string* tmp_rep);
	int number();
	int id();
	
	protected:
	void run();
	void runBis();
	
	bool Alignement_sequences;
	string* Alignement_first_seq;
	string* Alignement_second_seq;
	string* Alignement_path;
	string* Alignement_tmp_rep;
	Fasta* Alignement_fasta_a;
	Fasta* Alignement_fasta_b;
	Hit* Alignement_hit_a;
	Hit* Alignement_hit_b;
	int Alignement_id;
	vector<double>* Alignement_identity;
	
	private:
	void align_pipe();
	void align();
	void read(string* Fasta_file);
	double compute_identity();
	void trunquate_sequence();
	
	static string Alignement_salt;
};


#endif
