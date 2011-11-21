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

#include "ThreadNumber.hpp"

int ThreadNumber::ThreadNumber_number = 0;
mutex ThreadNumber::ThreadNumber_number_lock;
int ThreadNumber::ThreadNumber_max_number = -1;
mutex ThreadNumber::ThreadNumber_limit;

int ThreadNumber::number()
{
	lock_guard<mutex> lk(ThreadNumber_number_lock);
	return ThreadNumber_number;
}

void ThreadNumber::number_inc()
{
	lock_guard<mutex> lk(ThreadNumber_number_lock);
	ThreadNumber_number++;
	if(ThreadNumber::number() >= ThreadNumber_max_number)
		ThreadNumber_limit.lock();
}

void ThreadNumber::number_dec()
{
	lock_guard<mutex> lk(ThreadNumber_number_lock);
	ThreadNumber_number--;
	ThreadNumber_limit.unlock();
}

void ThreadNumber::set_max_number(int number)
{
	ThreadNumber_max_number = number;
}

void ThreadNumber::add_thread()
{
	ThreadNumber::number_inc();
}

void ThreadNumber::pop_thread()
{
	ThreadNumber::number_dec();
}


ThreadNumber::ThreadNumber()
{

}

ThreadNumber::~ThreadNumber()
{

}

