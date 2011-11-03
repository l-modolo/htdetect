#ifndef DEF_ProgressBarThread
#define DEF_ProgressBarThread

#include <iostream>
#include <mutex>
#include <math.h>

using namespace std;

class ProgressBarThread
{
	public:
	ProgressBarThread(int step, int step_max, int* start, int stop);
	
	void operator()();
	
	protected:
	int* ProgressBar_start;
	int ProgressBar_stop;
	int ProgressBar_step;
	int ProgressBar_step_max;
	chrono::time_point<std::chrono::system_clock> ProgressBar_time;
	
	private:
	void display();
};

#endif
