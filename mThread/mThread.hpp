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

#ifndef DEF_mThread
#define DEF_mThread

#include <exception>
#include <stdexcept>
#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include "mThreadWaiting.hpp"
#include "mThreadRunning.hpp"

using namespace std;

template <typename T>
class mThread
{
	public:
	mThread(int number);
	~mThread();

	void stop();
	void add(T);

	protected:
	mThreadWaiting<T> mThread_waiting;
	vector< mThreadRunning<T> > mThread_running;
};

//#include "mThread.tli"

template <typename T>
mThread<T>::mThread(int number) : mThread_waiting(number*2)
{
	for(int i = 0; i < number; i++)
	{
		mThread_running.push_back(mThreadRunning<T>(&mThread_waiting));
	}
}

template <typename T>
mThread<T>::~mThread()
{
	mThreadWaiting<T>::set_stop(true);
	for(int i = 0; i < mThread_running.size(); i++)
	{
		if(mThread_running.at(i).joinable())
			mThread_running.at(i).join();
	}
}

template <typename T>
void mThread<T>::add(T x)
{
	mThread_waiting.add(x);
}

template <typename T>
void mThread<T>::stop()
{
	mThreadWaiting<T>::set_stop(true);
	for(int i = 0; i < mThread_running.size(); i++)
	{
		mThread_running.at(i).join();
	}
}

#endif

