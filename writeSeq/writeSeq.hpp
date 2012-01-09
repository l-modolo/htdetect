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
#include "../mThread/mThread.hpp"
#include "../Alignement/Alignement.hpp"

using namespace std;

class writeSeq
{
	public:
	writeSeq(string output);
	~writeSeq();
	
	void add(Hit* qhit, string* query, Hit* thit, string* target, mutex* controler);
	bool write();
	
	void stop();
	
	int size();
	
	protected:
	void push_back(Hit qhit, string* query, Hit thit, string* target, mutex* controler);
	bool pop_front();
	
	void run();
	void thread_run();
	
	void set_run(bool run);
	
	static bool writeSeq_init;
	static bool writeSeq_run;
	static thread writeSeq_thread;
	static string writeSeq_output;
	static deque<Hit> writeSeq_qhit;
	static deque<Hit> writeSeq_thit;
	static deque<string*> writeSeq_query;
	static deque<string*> writeSeq_target;
	static deque<mutex*> writeSeq_controler;
	
	static ofstream writeSeq_qoutputf;
	static ofstream writeSeq_toutputf;
	
	static mutex writeSeq_onebyone;
	static mutex writeSeq_empty;
	static mutex writeSeq_full;
	static condition_variable writeSeq_empty_cond;
	static condition_variable writeSeq_full_cond;
	
	friend class Alignement;
	friend class mThread<class Alignement>;
	friend class mThreadRunning<class Alignement>;
	friend class mThreadWaiting<class Alignement>;
};

#endif

