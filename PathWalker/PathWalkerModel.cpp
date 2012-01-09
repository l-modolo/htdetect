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

#include "PathWalkerModel.hpp"

PathWalkerModel::PathWalkerModel(double chromosome_identity, vector<double>* hit_identity, bool verbose)
{
	PathWalker_verbose = verbose;
	PathWalker_chromosome_identity = chromosome_identity;
	PathWalker_Hit_identity = hit_identity;
}

PathWalkerModel::~PathWalkerModel()
{
	
}

void PathWalkerModel::add(unsigned int query, Hit* hit_query, Hit* hit_target)
{
	// we try to add the hit to a previous path if possible
	// elsewise we add it to a new path
	int id = test_to_path(query, hit_query, hit_target);
	add_to_path(id, query, hit_query, hit_target);
}

int PathWalkerModel::test_to_path(int query, Hit* hit_query, Hit* hit_target)
{
	try
	{
		bool new_path = false;
		if(query == 0)
		{
			PathWalker_QueryToPath.push_back(vector<unsigned int>());
			PathWalker_QueryIdToPath.push_back(vector<unsigned int>());
			new_path = true;
		}
		while(query_number_size() <= query)
		{
			PathWalker_QueryToPath.push_back(vector<unsigned int>());
			PathWalker_QueryIdToPath.push_back(vector<unsigned int>());
			new_path = true;
		}
		if(!new_path)
		{
			for(int i = 0; i < query_number_size(query); i++)
			{
				if(PathWalker_PathList.at(query_number(query).at(i)).test(hit_query, hit_target))
					return query_number(query).at(i);
			}
		}
		return -1;
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : bool PathWalkerModel::test_to_path(int i, Hit* hit_query, Hit* hit_target)" << endl;
	}
}

void PathWalkerModel::add_to_path(int id, int query, Hit* hit_query, Hit* hit_target)
{
	try
	{
		if(id < PathWalker_PathList.size() && id != -1)
		{
			PathWalker_PathList.at(id).add(hit_query, hit_target);
			query_number(query).push_back(id);
			query_id(query).push_back(hit_query->id());
		}
		else
		{
			PathWalker_pvalue.push_back(-1.0);
			PathWalker_PathList.push_back(Path(PathWalker_chromosome_identity, PathWalker_Hit_identity, &PathWalker_pvalue.back(), PathWalker_verbose));
			PathWalker_PathList.back().add(hit_query, hit_target);
			PathWalker_QueryToPath.at(query).push_back(PathWalker_PathList.size()-1);
			PathWalker_QueryIdToPath.at(query).push_back(hit_query->id());
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void PathWalkerModel::add_to_path(int i, Hit* hit_query, Hit* hit_target)" << endl;
	}
}

int PathWalkerModel::query_number_size()
{
	return PathWalker_QueryToPath.size();
}

int PathWalkerModel::query_id_size()
{
	return PathWalker_QueryIdToPath.size();
}

int PathWalkerModel::query_number_size(int i)
{
	try
	{
		return PathWalker_QueryToPath.at(i).size();
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : int query_number_size(int i)" << endl;
	}
}

int PathWalkerModel::query_id_size(int i)
{
	try
	{
		return PathWalker_QueryIdToPath.at(i).size();
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : int query_number_size(int i)" << endl;
	}
}

vector<unsigned int> & PathWalkerModel::query_number(int i)
{
	try
	{
		return PathWalker_QueryToPath.at(i);
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : unsigned int query_number(int i, int j)" << endl;
	}
}

vector<unsigned int> & PathWalkerModel::query_id(int i)
{
	try
	{
		return PathWalker_QueryIdToPath.at(i);
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : unsigned int query_number(int i, int j)" << endl;
	}
}


