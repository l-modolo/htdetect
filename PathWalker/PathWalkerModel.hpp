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

#ifndef DEF_PathWalkerModel
#define DEF_PathWalkerModel

#include "../Path/Path.hpp"
#include "../mThread/mThread.hpp"
#include "../ProgressBar/ProgressBar.hpp"

using namespace std;

class PathWalkerModel
{
	public:
	PathWalkerModel(double chromosome_identity, vector<double>* hit_identity, bool verbose);
	~PathWalkerModel();
	
	void add(unsigned int query_number, Hit* hit_query, Hit* hit_target);
	
	protected:
	int test_to_path(int query, Hit* hit_query, Hit* hit_target);
	void add_to_path(int id, int query, Hit* hit_query, Hit* hit_target);
	int query_number_size();
	int query_number_size(int i);
	vector<unsigned int> & query_number(int i);
	
	bool PathWalker_verbose;
	
	double PathWalker_chromosome_identity;
	vector<double>* PathWalker_Hit_identity;
	
	vector<Path> PathWalker_PathList;
	vector<double> PathWalker_pvalue;
	vector<vector<unsigned int>> PathWalker_QueryToPath;
	
};

#endif

