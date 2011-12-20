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

#ifndef DEF_writeSeq
#define DEF_writeSeq

#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <string>
#include <deque>
#include "../Hit/Hit.hpp"

using namespace std;

class writeSeq
{
	public:
	writeSeq(string output);
	~writeSeq();
	
	void add(Hit* qhit, string* query, Hit* thit, string* target);
	void write();
	
	int size();
	
	protected:
	void push_back(Hit* qhit, string* query, Hit* thit, string* target);
	void pop_front();
	
	void run();
	void thread_run();
	
	void set_run(bool run);
	bool get_run();
	
	bool writeSeq_run;
	thread writeSeq_thread;
	string writeSeq_output;
	deque<Hit*> writeSeq_qhit;
	deque<Hit*> writeSeq_thit;
	deque<string*> writeSeq_query;
	deque<string*> writeSeq_target;
	
	ofstream writeSeq_qoutputf;
	ofstream writeSeq_toutputf;
	
	static mutex writeSeq_onebyone;
	static mutex writeSeq_empty;
	static mutex writeSeq_full;
	static condition_variable writeSeq_empty_cond;
	static condition_variable writeSeq_full_cond;
};

#endif

