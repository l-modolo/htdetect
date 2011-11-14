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

#include "PairWalkerModel.hpp"

PairWalkerModel::PairWalkerModel(bool verbose)
{
	PairWalker_verbose = verbose;
}

PairWalkerModel::PairWalkerModel(PairWalkerModel & PairWalkerbis)
{
	PairWalker_fasta_a = PairWalkerbis.PairWalker_fasta_a;
	PairWalker_fasta_b = PairWalkerbis.PairWalker_fasta_b;
	PairWalker_muscle_path = PairWalkerbis.PairWalker_muscle_path;
	PairWalker_file = PairWalkerbis.PairWalker_file;
	PairWalker_name = PairWalkerbis.PairWalker_name;
	PairWalker_verbose = PairWalkerbis.PairWalker_verbose;
	
	PairWalker_query = PairWalkerbis.PairWalker_query;
	PairWalker_target = PairWalkerbis.PairWalker_target;
	
	for(auto & it : PairWalkerbis.PairWalker_target)
	{
		it = nullptr;
	}
	
	PairWalker_neighbor_prev = PairWalkerbis.PairWalker_neighbor_prev;
	PairWalker_neighbor_next = PairWalkerbis.PairWalker_neighbor_next;
	PairWalker_identity = PairWalkerbis.PairWalker_identity;
	PairWalker_pvalue = PairWalkerbis.PairWalker_pvalue;
}

PairWalkerModel::~PairWalkerModel()
{
	for(auto & it : PairWalker_target)
	{
		if(it != nullptr)
			delete it;
	}
}


