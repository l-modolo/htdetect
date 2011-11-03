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
	if(step < ProgressBar_stop)
	{
		cout << ProgressBar_step << "/" << ProgressBar_step_max << " : " << round(((double)step/(double)ProgressBar_stop*100.0) * 100) / 100 << "%";
	
		auto timediff = (chrono::system_clock::now() - ProgressBar_time);
		auto time = timediff.count();
	
		double speed = (double)(time / 1000000) / (double)step;
		double sec = speed * (double)(ProgressBar_stop - step);
		double min = floor(sec / 60);
	
		cout << " and " << min << " min " << floor(sec - min*60) << " sec left at "<< (double)step / (double)(time / 1000000) << " step/sec.                                                    \r";
	}
	else
		cout << ProgressBar_step << "/" << ProgressBar_step_max << " : 100%                                                                                  " << endl;
}

