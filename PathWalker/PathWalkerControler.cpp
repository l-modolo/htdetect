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

#include "PathWalkerControler.hpp"


PathWalkerControler::PathWalkerControler(double chromosome_identity, vector<double>* hit_identity, bool verbose) : PathWalkerModel::PathWalkerModel(chromosome_identity, hit_identity, verbose) {}

void PathWalkerControler::compute_pvalue(int thread_number)
{
	mThread<Path> alignements_run(thread_number);
	ProgressBar progress(1, 3, 0,PathWalker_PathList.size(), PathWalker_verbose);
	
	for(int i = 0; i< PathWalker_PathList.size(); i++)
	{
		alignements_run.add(PathWalker_PathList.at(i));
		progress.inc();
	}
	alignements_run.stop();
}

void PathWalkerControler::rm_overlapping_Path(int thread_number)
{
	ProgressBar progress(2, 3, 0,PathWalker_PathList.size(), PathWalker_verbose);
	
	for(int i = 0; i < query_number_size(); i++)
	{
		
		progress.inc();
	}
}

