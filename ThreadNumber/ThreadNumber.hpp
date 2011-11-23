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

#ifndef DEF_ThreadNumber
#define DEF_ThreadNumber

#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class ThreadNumber
{
	public:
	ThreadNumber();
	~ThreadNumber();
	
	static void set_max_number(int number);
	static int number();
	static int max_number();
	static void add_thread();
	static void pop_thread();
	
	protected:
	static void number_inc();
	static void number_dec();
	
	static int ThreadNumber_number;
	static mutex ThreadNumber_number_lock;
	static int ThreadNumber_max_number;
	static mutex ThreadNumber_limit;
	static condition_variable ThreadNumber_limit_cond;
	
	static list<thread> test;
};
#endif

