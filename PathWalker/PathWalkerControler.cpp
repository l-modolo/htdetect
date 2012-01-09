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
	try
	{
		// we compute the p-value for each path (as an hit sequences)
		mThread<Path> alignements_run(thread_number);
		ProgressBar progress(1, 3, 0,PathWalker_PathList.size(), PathWalker_verbose);
		
		for(int i = 0; i< PathWalker_PathList.size(); i++)
		{
			alignements_run.add(PathWalker_PathList.at(i));
			progress.inc();
		}
		alignements_run.stop();
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void PathModel::add(Hit* hit_query, Hit* hit_target)" << endl;
	}
}

void PathWalkerControler::rm_overlapping_Path(int thread_number)
{
	ProgressBar progress(2, 3, 0,PathWalker_PathList.size(), PathWalker_verbose);
	double min_pvalue = 2.0;
	int query;
	int id;
	vector<unsigned int> query_to_keep;
	vector<unsigned int> id_to_keep;
	
	int overallsize = 0;
	for(int i = 0; i< PathWalker_PathList.size(); i++)
	{
		overallsize += PathWalker_PathList.at(i).size();
	}
	
	// for a giver position we only keep the path with the loest p-value
	for(int i = 0; i < query_number_size(); i++)
	{
		if(query_number_size(i) > 1)
		{
			min_pvalue = 2.0;
			// we use the p-value and not the statistic because we work on many différent poisson distribution
			// as p-value are borned to 1 in case of multiples path with a p-value = 1, we choose the first one (which can change between différent runs)
			// but is does't mater for the study as by definition we are going to discard the hit with a p-value egal to one.
			query_to_keep.clear();
			id_to_keep.clear();
			
			for(int j = 0; j < query_number_size(i); j++)
			{
				if(min_pvalue > PathWalker_pvalue.at(query_number(i).at(j)))
				{
					query = query_number(i).at(j);
					id = query_id(i).at(j);
					min_pvalue = PathWalker_pvalue.at(query);
				}
			}
			
			for(int j = 0; j < query_number_size(i); j++)
			{
				if(query != query_number(i).at(j))
				{
					if(!PathWalker_PathList.at(query_number(i).at(j)).rm_front(query_id(i).at(j)))
					{
						query_to_keep.push_back(query_number(i).at(j));
						id_to_keep.push_back(query_id(i).at(j));
					}
				}
			}
			query_to_keep.push_back(query);
			id_to_keep.push_back(id);
			query_number(i) = query_to_keep;
			query_id(i) = id_to_keep;
		}
		progress.inc();
	}
	
	overallsize = 0;
	for(int i = 0; i< PathWalker_PathList.size(); i++)
	{
		overallsize += PathWalker_PathList.at(i).size();
	}
	
	// we do the same thing in reverse order to be sure to have no doublon left
	for(int i = query_number_size()-1; 0 <= i; i--)
	{
		if(query_number_size(i) > 1)
		{
			min_pvalue = 2.0;
			query_to_keep.clear();
			id_to_keep.clear();
			
			for(int j = 0; j < query_number_size(i); j++)
			{
				if(min_pvalue > PathWalker_pvalue.at(query_number(i).at(j)))
				{
					query = query_number(i).at(j);
					id = query_id(i).at(j);
					min_pvalue = PathWalker_pvalue.at(query);
				}
			}
			
			for(int j = 0; j < query_number_size(i); j++)
			{
				if(query != query_number(i).at(j))
				{
					if(!PathWalker_PathList.at(query_number(i).at(j)).rm_back(query_id(i).at(j)))
					{
						query_to_keep.push_back(query_number(i).at(j));
						id_to_keep.push_back(query_id(i).at(j));
					}
				}
			}
			query_to_keep.push_back(query);
			id_to_keep.push_back(id);
			query_number(i) = query_to_keep;
			query_id(i) = id_to_keep;
		}
		progress.inc();
	}
	
	overallsize = 0;
	for(int i = 0; i< PathWalker_PathList.size(); i++)
	{
		overallsize += PathWalker_PathList.at(i).size();
	}
}

