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

#include "myThread.hpp"

int myThread::myThread_number = 0;
mutex myThread::myThread_number_lock;
int myThread::myThread_max_number = -1;
mutex myThread::myThread_limit;

int myThread::number()
{
	lock_guard<mutex> lk(myThread_number_lock);
	return myThread_number;
}

int myThread::number_inc()
{
	lock_guard<mutex> lk(myThread_number_lock);
	myThread_number++;
	if(myThread_number >= myThread_max_number)
		myThread_limit.lock();
}

int myThread::number_dec()
{
	lock_guard<mutex> lk(myThread_number_lock);
	myThread_number--;
	myThread_limit.unlock();
}

void myThread::set_max_number(int number)
{
	myThread_max_number = number;
}

myThread::myThread() : thread::thread()
{
	try
	{
		if(myThread_max_number == -1)
			throw logic_error("There is no thread number limit");
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : myThread::myThread()" << endl;
	}
	joined = false;
}

template<typename _Callable , typename... _Args> myThread::myThread(_Callable &&__f, _Args &&...__args)
{
	try
	{
		if(myThread_max_number == -1)
			throw logic_error("There is no thread number limit");
		
		number_inc();
		myThread_limit.lock();
		thread::thread(__f, __args...);
		myThread_limit.unlock();
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : myThread::myThread()" << endl;
	}
	joined = false;
}

myThread::~myThread()
{
	if(myThread_max_number != -1)
	{
		if(!joined)
		{
			number_dec();
			thread::detach();
		}
	}
}

void myThread::join()
{
	thread::join();
	joined = true;
	number_dec();
}
void myThread::detach()
{
	thread::detach();
	joined = true;
	number_dec();
}

