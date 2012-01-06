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

#ifndef DEF_mThreadWaiting
#define DEF_mThreadWaiting

#include <future>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
class mThreadWaiting
{
	public:
	mThreadWaiting(int size);
	~mThreadWaiting();
	
	void add(T const & x);
	T* get();
	
	static bool stop();
	static bool stop_all();
	static void set_stop(bool run);
	static bool run();
	
	protected:
	void push_back(T const & x);
	T* pop_front();
	static int size();
	
	static void set_run(bool run);
	
	static mutex mThread_onebyone;
	static mutex mThread_empty;
	static mutex mThread_full;
	static condition_variable mThread_empty_cond;
	static condition_variable mThread_full_cond;
	
	static int mThread_size;
	static int mThread_pos_front;
	static int mThread_pos_back;
	static deque<T> mThread_waiting;
	
	static bool mThread_run;
	static mutex mThread_run_controler;
	static bool mThread_stop_signal;
	static mutex mThread_stop_controler;
	
	static bool mThread_init;
};
#include "mThreadWaiting.tli"
#endif

