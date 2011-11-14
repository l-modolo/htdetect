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

#ifndef DEF_PairWalkerModel
#define DEF_PairWalkerModel

#include "../HitList/HitList.hpp"
#include "../Fasta/Fasta.hpp"
#include "../ProgressBar/ProgressBar.hpp"

using namespace std;

class PairWalkerModel
{
	public:
	PairWalkerModel(bool verbose);
	PairWalkerModel(PairWalkerModel & PairWalkerbis);
	~PairWalkerModel();
	
	protected:
	
	Fasta* PairWalker_fasta_a;
	Fasta* PairWalker_fasta_b;
	string PairWalker_muscle_path;
	string PairWalker_file;
	string PairWalker_name;
	bool PairWalker_verbose;
	
	HitList PairWalker_query;
	vector<HitList*> PairWalker_target;
	
	vector<bool> PairWalker_neighbor_prev;
	vector<bool> PairWalker_neighbor_next;
	vector<double> PairWalker_identity;
	vector<double> PairWalker_pvalue;
	
};

#endif

