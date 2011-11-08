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

#include "ProgressBar.hpp"

int ProgressBar::ProgressBar_number = 0;

ProgressBar::ProgressBar(int step, int step_max, int start, int stop)
{
	try
	{
		if(ProgressBar_number < 1)
		{
			ProgressBar_number++;
			if(start < stop)
				ProgressBar_start =  start;
			else
				ProgressBar_start = 0;
			ProgressBar_stop = stop;
	
			ProgressBar_step = step;
			ProgressBar_step_max = step_max;
	
			ProgressBar_run = thread(ProgressBarThread(ProgressBar_step, ProgressBar_step_max, &ProgressBar_start, ProgressBar_stop));
		}
		else
		{
			throw logic_error("There already is a ProgressBar running");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in ProgressBar::ProgressBar(int step, int step_max, int start, int stop)" << endl;
	}
}

void ProgressBar::operator()(int step, int start, int stop)
{
	if(ProgressBar_start < ProgressBar_stop)
	{
		ProgressBar_start = ProgressBar_stop;
	}
	ProgressBar_run.join();
	
	if(start < stop)
		ProgressBar_start =  start;
	else
		ProgressBar_start = 0;
	ProgressBar_stop = stop;
	ProgressBar_step = step;
	
	ProgressBar_run = thread(ProgressBarThread(ProgressBar_step, ProgressBar_step_max, &ProgressBar_start, ProgressBar_stop));
}

ProgressBar::~ProgressBar()
{
	ProgressBar_start = ProgressBar_stop;
	ProgressBar_run.join();
	ProgressBar_number--;
}

void ProgressBar::inc()
{
	ProgressBar_start++;
}
