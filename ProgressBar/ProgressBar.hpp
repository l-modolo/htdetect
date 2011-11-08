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

#ifndef DEF_ProgressBar
#define DEF_ProgressBar

#include <chrono>
#include <thread>
#include "ProgressBarThread.hpp"

using namespace std;

class ProgressBar {
	public:
	ProgressBar(int step, int step_max, int start, int stop, bool verbose);
	~ProgressBar();
	
	void operator()(int step, int start, int stop);
	void inc();
	
	protected:
	int ProgressBar_start;
	int ProgressBar_stop;
	int ProgressBar_step;
	int ProgressBar_step_max;
	bool ProgressBar_verbose;
	thread ProgressBar_run;
	
	void run();
	
	static int ProgressBar_number;
};


#endif
