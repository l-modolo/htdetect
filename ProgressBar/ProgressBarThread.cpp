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

#include "ProgressBarThread.hpp"

ProgressBarThread::ProgressBarThread(int step, int step_max, int* start, int stop)
{
	ProgressBar_start = start;
	ProgressBar_stop = stop;
	ProgressBar_step = step;
	ProgressBar_step_max = step_max;
}

void ProgressBarThread::operator()()
{
	ProgressBar_time = chrono::system_clock::now();
	
	while(*ProgressBar_start < ProgressBar_stop)
	{
		usleep(100000);
		display();
	}
}

void ProgressBarThread::display()
{
	int step = *ProgressBar_start;
	cout << "\r";
	cout << ProgressBar_step << "/" << ProgressBar_step_max << " : " << round(((double)step/(double)ProgressBar_stop*100.0) * 100) / 100 << "%";
	
	auto timediff = (chrono::system_clock::now() - ProgressBar_time);
	auto time = timediff.count();
	
	double speed = (double)(time / 1000000) / (double)step;
	double sec = speed * (double)(ProgressBar_stop - step);
	double min = floor(sec / 60);
	
	cout << " and " << min << " min " << floor(sec - min*60) << " sec left at "<< (double)step / (double)(time / 1000000) << " step/sec.                                                    ";
	
	if(step >= ProgressBar_stop)
		cout << endl;
}

