#ifndef DEF_ProgressBar
#define DEF_ProgressBar

#include <chrono>
#include <thread>
#include "ProgressBarThread.hpp"

using namespace std;

class ProgressBar {
	public:
	ProgressBar(int step, int step_max, int start, int stop);
	~ProgressBar();
	
	void operator()(int step, int start, int stop);
	void inc();
	
	protected:
	int ProgressBar_start;
	int ProgressBar_stop;
	int ProgressBar_step;
	int ProgressBar_step_max;
	thread ProgressBar_run;
	
	void run();
	
	static int ProgressBar_number;
};


#endif
