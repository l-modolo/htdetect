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
#include <ctype.h>
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
	Alignement(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, string* muscle_path, int thread_id , string* tmp_rep);
	
	int number();
	int id();
	
	protected:
	
	string* Alignement_first_seq;
	string* Alignement_second_seq;
	
	string* Alignement_path;
	string* Alignement_tmp_rep;
	Fasta* Alignement_fasta_a;
	Fasta* Alignement_fasta_b;
	Hit* Alignement_hit_a;
	Hit* Alignement_hit_b;
	int Alignement_id;
	
	void align();
	void read(string* Fasta_file);
	
	static string Alignement_salt;
	
	bool Alignement_init;
	
	void complementary(string * seq);
	
	friend class writeSeq;
};


#endif
