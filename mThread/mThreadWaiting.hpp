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
#include <queue>
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
class mThreadWaiting
{
	public:
	mThreadWaiting(int size);
	
	void add(T);
	T get();
	
	protected:
	static mutex mThread_empty;
	static mutex mThread_full;
	static condition_variable mThread_empty_cond;
	static condition_variable mThread_full_cond;
	
	int mThread_size;
	queue<T> mThread_waiting;
};
#include "mThreadWaiting.tli"
#endif

