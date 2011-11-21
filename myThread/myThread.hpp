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

#ifndef DEF_myThread
#define DEF_myThread

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

class myThread : public thread
{
	public:
	myThread();
	
	template<typename _Callable , typename... _Args> myThread(_Callable &&__f, _Args &&...__args);
	
	void join();
	void detach();
	
	~myThread();
	
	static void set_max_number(int number);
	static int number();
	static int number_inc();
	static int number_dec();
	
	protected:
	bool joined;
	static int myThread_number;
	static mutex myThread_number_lock;
	static int myThread_max_number;
	static mutex myThread_limit;
};
#endif

