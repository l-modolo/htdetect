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

#include "writeSeq.hpp"
bool writeSeq::writeSeq_init = false;

mutex writeSeq::writeSeq_onebyone;
mutex writeSeq::writeSeq_empty;
mutex writeSeq::writeSeq_full;
condition_variable writeSeq::writeSeq_empty_cond;
condition_variable writeSeq::writeSeq_full_cond;

bool writeSeq::writeSeq_run;
thread writeSeq::writeSeq_thread;

string writeSeq::writeSeq_output;
deque<Hit> writeSeq::writeSeq_qhit;
deque<Hit> writeSeq::writeSeq_thit;
deque<string*> writeSeq::writeSeq_query;
deque<string*>writeSeq:: writeSeq_target;
deque<mutex*> writeSeq::writeSeq_controler;

ofstream writeSeq::writeSeq_qoutputf;
ofstream writeSeq::writeSeq_toutputf;

writeSeq::writeSeq(string output)
{
	try
	{
		if(!writeSeq_init)
		{
			writeSeq_init = true;
			writeSeq_output = output;
			set_run(true);
			writeSeq_qoutputf.open(writeSeq_output+".query");
			writeSeq_toutputf.open(writeSeq_output+".target");
			
			if(!writeSeq_qoutputf || !writeSeq_toutputf)
				throw logic_error("Can not open "+writeSeq_output+".query"+" or "+writeSeq_output+".target");
			
			writeSeq::run();
		}
		else
		{
			throw logic_error("writeSeq is a static object");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << endl;
	}
}

writeSeq::~writeSeq()
{
	set_run(false);
	if(writeSeq_thread.joinable())
		writeSeq_thread.join();
	
	writeSeq_qoutputf.close();
	writeSeq_toutputf.close();
	writeSeq_init = false;
}

void writeSeq::stop()
{
//	cout << writeSeq_qhit.size() << "\t" << writeSeq_thit.size() << "\t" << writeSeq_query.size() << "\t" << writeSeq_target.size() << "\t" << writeSeq_controler.size();
	set_run(false);
	writeSeq_thread.join();
}

void writeSeq::add(Hit* qhit, string* query, Hit* thit, string* target, mutex* controler)
{
	try
	{
		unique_lock<mutex> full(writeSeq_full);
		
		while(writeSeq::size() >= 1000)
		{
			writeSeq_full_cond.wait(full);
		}
		
		writeSeq::push_back(*qhit, query, *thit, target, controler);
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void writeSeqWaiting<T>::add(T const & x)" << endl;
		exit(-1);
	}
}

void writeSeq::push_back(Hit qhit, string* query, Hit thit, string* target, mutex* controler)
{
	unique_lock<mutex> lk(writeSeq_onebyone);
	
	writeSeq_qhit.push_back(qhit);
	writeSeq_thit.push_back(thit);
	writeSeq_query.push_back(query);
	writeSeq_target.push_back(target);
	writeSeq_controler.push_back(controler);
	
	writeSeq_empty_cond.notify_one();
}

void writeSeq::write()
{
	try
	{
//		cout << "w" << writeSeq_thit.front().id() << endl;
		
		unique_lock<mutex> empty(writeSeq_empty);
		
		while(writeSeq_query.size() <= 0 && writeSeq::get_run())
		{
			writeSeq_empty_cond.wait(empty);
		}
		
		if(writeSeq_query.size() > 0)
		{
			writeSeq::pop_front();
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : T writeSeqWaiting<T>::get()" << endl;
		exit(-1);
	}
}

void writeSeq::pop_front()
{
	unique_lock<mutex> lk(writeSeq_onebyone);
	try
	{
			writeSeq_controler.front()->lock();
			
			writeSeq_qoutputf << ">" << writeSeq_qhit.front() << "\t" << writeSeq_thit.front() << endl;
			writeSeq_qoutputf << *(writeSeq_query.front()) << endl;
			
			writeSeq_toutputf << ">" << writeSeq_qhit.front() << "\t" << writeSeq_thit.front() << endl;
			writeSeq_toutputf << *(writeSeq_target.front()) << endl;
			
			delete writeSeq_query.front();
			delete writeSeq_target.front();
			
			writeSeq_controler.front()->unlock();
			delete writeSeq_controler.front();
			
			writeSeq_qhit.pop_front();
			writeSeq_thit.pop_front();
			writeSeq_query.pop_front();
			writeSeq_target.pop_front();
			writeSeq_controler.pop_front();
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << endl;
	}
	
	writeSeq_full_cond.notify_one();
}

int writeSeq::size()
{
	unique_lock<mutex> lk(writeSeq_onebyone);
	return writeSeq_query.size();
}

void writeSeq::run()
{
	try
	{
		writeSeq_thread = thread(&writeSeq::thread_run, this );
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void writeSeq::run()" << endl;
	}
}

void writeSeq::thread_run()
{
	try
	{
		while(writeSeq::get_run() || writeSeq_query.size() > 0)
		{
			writeSeq::write();
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void writeSeq::thread_run()" << endl;
	}
}

void writeSeq::set_run(bool run)
{
	unique_lock<mutex> lk(writeSeq_onebyone);
	writeSeq_run = run;
	if(!run)
	{
		writeSeq_empty_cond.notify_one();
	}
}
bool writeSeq::get_run()
{
	unique_lock<mutex> lk(writeSeq_onebyone);
	return writeSeq_run;
}


