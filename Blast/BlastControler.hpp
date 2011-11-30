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
#include "BlastModel.hpp"
#include "../Alignement/Alignement.hpp"
#include "../pTest/pTest.hpp"
#include "../mThread/mThread.hpp"
#include "../PathWalker/PathWalker.hpp"

using namespace std;

class BlastControler : public BlastModel
{
	public:
	BlastControler(bool verbose);
	~BlastControler();
	
	void sort();
	void neighbor();
	void remove_overlapping();
	void remove_overlapping_2(double chromosome_identity, int thread_number);
	void compute_identity(int thread_number, string tmp_rep);
	void compute_test(double chromosome_identity, int thread_number);
	
	private:
	void parallel_remove_overlapping();
	void parallel_compute_test(double chromosome_identity, unsigned int i, unsigned int j, list< thread >* alignements_run, int thread_number);
	void hitTest(double chromosome_identity,  unsigned int i, unsigned int j);
	
	void clean_thread_list(list<thread>* locks, int thread_number, bool* run);
};
#endif

