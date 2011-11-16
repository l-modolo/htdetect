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
#include "../Fasta/Fasta.hpp"
#include "../ProgressBar/ProgressBar.hpp"

using namespace std;

class PathWalkerModel
{
	public:
	PathWalkerModel(bool verbose);
	~PathWalkerModel();
	
	protected:
	
	Fasta* PathWalker_fasta_a;
	Fasta* PathWalker_fasta_b;
	string PathWalker_muscle_path;
	string PathWalker_file;
	string PathWalker_name;
	bool PathWalker_verbose;
	
	vector<Hit*> PathWalker_query;
	
	vector<int> PathWalker_size;
	vector<double> PathWalker_identity;
	vector<double> PathWalker_pvalue;
	
};

#endif

