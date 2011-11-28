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

#ifndef DEF_mThreadRunning
#define DEF_mThreadRunning

#include <future>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "mThreadWaiting.hpp"
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
class mThreadRunning
{
	public:
	mThreadRunning(mThreadWaiting<T>* todo);

	static bool get_run();
	static void set_run();
	void join();

	protected:
	void run();
	void thread_run();

	static mutex mThread_onebyone;

	mThreadWaiting<T>* mThread_todo;
	thread mThread_thread;

	static bool mThread_run;
	static mutex mThread_controler;
};

#include "mThreadRunning.tli"
#endif
