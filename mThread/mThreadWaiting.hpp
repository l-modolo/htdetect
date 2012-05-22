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

//#include "mThreadWaiting.tli"

template <typename T>
bool mThreadWaiting<T>::mThread_init = false;

template<typename T>
mutex mThreadWaiting<T>::mThread_onebyone;
template<typename T>
mutex mThreadWaiting<T>::mThread_empty;
template<typename T>
mutex mThreadWaiting<T>::mThread_full;
template<typename T>
condition_variable mThreadWaiting<T>::mThread_empty_cond;
template<typename T>
condition_variable mThreadWaiting<T>::mThread_full_cond;

template<typename T>
int mThreadWaiting<T>::mThread_size;
template<typename T>
int mThreadWaiting<T>::mThread_pos_front;
template<typename T>
int mThreadWaiting<T>::mThread_pos_back;
template<typename T>
deque<T> mThreadWaiting<T>::mThread_waiting;

template<typename T>
bool mThreadWaiting<T>::mThread_run = true;
template<typename T>
mutex mThreadWaiting<T>::mThread_run_controler;
template<typename T>
bool mThreadWaiting<T>::mThread_stop_signal = false;
template<typename T>
mutex mThreadWaiting<T>::mThread_stop_controler;

template <typename T>
bool mThreadWaiting<T>::run()
{
	unique_lock<mutex> lk(mThread_onebyone);
	return mThread_run;
}

template <typename T>
void mThreadWaiting<T>::set_run(bool run)
{
	unique_lock<mutex> lk(mThread_onebyone);
	mThread_run = run;
	if(!run)
		mThread_empty_cond.notify_one();
}

template <typename T>
bool mThreadWaiting<T>::stop()
{
	unique_lock<mutex> lk(mThread_onebyone);
	return mThread_stop_signal;
}

template <typename T>
bool mThreadWaiting<T>::stop_all()
{
	mThread_full_cond.notify_all();
	mThread_empty_cond.notify_all();
}

template <typename T>
void mThreadWaiting<T>::set_stop(bool run)
{
	unique_lock<mutex> lk(mThread_onebyone);
	mThread_stop_signal = run;
	mThread_empty_cond.notify_one();
}

template<typename T>
mThreadWaiting<T>::mThreadWaiting(int size)
{
	try
	{
		if(!mThread_init)
		{
			mThreadWaiting<T>::mThread_init = true;
			mThreadWaiting<T>::mThread_run = true;
			mThreadWaiting<T>::mThread_stop_signal = false;
			mThreadWaiting<T>::mThread_size = size;
			mThreadWaiting<T>::mThread_pos_front = -1;
			mThreadWaiting<T>::mThread_pos_back = -1;
			mThreadWaiting<T>::mThread_waiting.clear();
		}
		else
		{
			throw logic_error("mThread is a static object");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : mThreadWaiting<T>::mThreadWaiting(int size)" << endl;
	}
}

template<typename T>
mThreadWaiting<T>::~mThreadWaiting()
{
	mThread_init = false;
}

template<typename T>
void mThreadWaiting<T>::add(T const & x)
{
	try
	{
		unique_lock<mutex> full(mThread_full);
		
		while(mThreadWaiting<T>::size() >= mThread_size - 1)
		{
			mThread_full_cond.wait(full);
		}
		
		mThreadWaiting<T>::push_back(x);
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void mThreadWaiting<T>::add(T const & x)" << endl;
		exit(-1);
	}
}

template<typename T>
T* mThreadWaiting<T>::get()
{
	try
	{
		unique_lock<mutex> empty(mThread_empty);
		
		while(mThreadWaiting<T>::size() <= 0)
		{
			mThread_empty_cond.wait(empty);
		}
		
		return mThreadWaiting<T>::pop_front();
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : T mThreadWaiting<T>::get()" << endl;
		exit(-1);
	}
}

template<typename T>
void mThreadWaiting<T>::push_back(T const & x)
{
	unique_lock<mutex> lk(mThread_onebyone);
	mThread_waiting.push_back(x);
	mThread_empty_cond.notify_one();
}

template<typename T>
T* mThreadWaiting<T>::pop_front()
{
	try
	{
		unique_lock<mutex> lk(mThread_onebyone);
		
		if(mThread_stop_signal)
		{
			mThread_run = false;
			mThread_empty_cond.notify_all();
		}
		
		T* value;
		
		if(mThread_waiting.size() <= 0)
		{
			value = nullptr;
		}
		else
		{
			value = new T(mThread_waiting.front());
			mThread_waiting.pop_front();
		}
		mThread_full_cond.notify_one();
		
		return value;
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : T mThreadWaiting<T>::pop_front()" << endl;
		exit(-1);
	}
}

template<typename T>
int mThreadWaiting<T>::size()
{
	unique_lock<mutex> lk(mThread_onebyone);
	if(mThread_run)
		return mThread_waiting.size();
	else
		return mThread_size;
}

#endif

