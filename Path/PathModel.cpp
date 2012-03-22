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

#include "PathModel.hpp"

int PathModel::Path_error = 0;

PathModel::PathModel(double chromosome_identity, vector<pair<long int, long int>>* identity, double* pvalue, bool verbose)
{
	Path_verbose = verbose;
	
	Path_size = 0;
	Path_identity.first = -1;
	Path_identity.second = -1;
	Path_pvalue = pvalue;
	
	Path_chromosome_identity = chromosome_identity;
	Path_hits_identity = identity;
}

PathModel::~PathModel()
{
	
}

PathModel& PathModel::operator=(PathModel const& pathModel)
{
	Path_verbose = pathModel.Path_verbose;
	
	Path_query = pathModel.Path_query;
	Path_target = pathModel.Path_target;
	
	Path_size = pathModel.Path_size;
	Path_identity = pathModel.Path_identity;
	Path_pvalue = pathModel.Path_pvalue;
	
	Path_chromosome_identity = pathModel.Path_chromosome_identity;
	Path_hits_identity = pathModel.Path_hits_identity;
}

bool PathModel::test(Hit* hit_query, Hit* hit_target) //test if the hit can be added to the path
{
	if(hit_query->set() && hit_target->set())
	{
		if(Path_query.size() > 0 && Path_target.size() > 0)
		{
			// target and hit must have the same chromosome
			if(Path_query.at(0)->name().compare(hit_query->name()) != 0)
				return false;
			
			if(Path_target.at(0)->name().compare(hit_target->name()) != 0)
				return false;
			
			// target and hit must have the same sens
			if(hit_query->sens() != Path_query.back()->sens())
				return false;
			if(hit_target->sens() !=  Path_target.back()->sens())
				return false;
			
			//target and hit must 
			if(*hit_query < *(Path_query.back()))
				return false;
			if(*hit_target < *(Path_target.back()))
				return false;
			
			if(hit_query->start() - (Path_query.back())->stop() >= 50000)
				return false;
			
			return true;
		}
		else
			return true;
	}
}

void PathModel::add(Hit* hit_query, Hit* hit_target)
{
	try
	{
		if(hit_query->set() && hit_target->set())
		{
			if(Path_query.size() > 0 && Path_target.size() > 0)
			{
				if(Path_query.at(0)->name().compare(hit_query->name()) != 0)
					throw logic_error("Query Hit not from the same chromosome as the reste of the Query Hit of this Path");
				
				if(Path_target.at(0)->name().compare(hit_target->name()) != 0)
					throw logic_error("Target Hit not from the same chromosome as the reste of the Target Hit of this Path");
				
				
				if(hit_query->sens() != Path_query.back()->sens())
				{
					throw logic_error("Wrong order of the Query Hit");
				}
				
				if(hit_target->sens() !=  Path_target.back()->sens())
				{
					throw logic_error("Wrong order of the Query Hit");
				}
				
				if(*hit_query < *(Path_query.back()))
				{
					throw logic_error("Wrong order of the Query Hit");
				}
				
				if(*hit_target < *(Path_target.back()))
				{
					throw logic_error("Wrong order of the Query Hit");
				}
			}
			Path_query.push_back(hit_query);
			Path_target.push_back(hit_target);
		}
		else
		{
			throw logic_error("invalid Hit");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void PathModel::add(Hit* hit_query, Hit* hit_target)" << endl;
	}
}

pair<Hit*, Hit*> PathModel::operator[](int i)
{
	return at(i);
}

pair<Hit*, Hit*> PathModel::at(int i)
{
	try
	{
		if(i < Path_query.size() && i < Path_target.size())
			return make_pair(Path_query.at(i),Path_target.at(i));
		else
			throw logic_error("i is out of range");
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : pair<Hit*, Hit*> PathModel::operator[](int i)" << endl;
	}
}

Hit* PathModel::target_hit(int id)
{
	try
	{
		for(int i = 0; i < Path_query.size(); i++)
		{
			if(Path_query.at(i)->id() == id)
			{
				return Path_target.at(i);
			}
		}
		throw logic_error("id not found");
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : Hit* PathModel::target_hit(int id)" << endl;
		exit(-1);
	}
}

bool PathModel::rm_front(int query_id)
{
	if(Path_query.front()->id() == query_id)
	{
		PathModel::pop_front();
		return true;
	}
	else
	{
		return false;
	}
}

bool PathModel::rm_back(int query_id)
{
	if(Path_query.back()->id() == query_id)
	{
		PathModel::pop_back();
		return true;
	}
	else
	{
		return false;
	}
}

void PathModel::pop_front()
{
	try
	{
		Path_query.erase(Path_query.begin());
		Path_target.erase(Path_target.begin());
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void PathModel::pop_front()" << endl;
	}
}

void PathModel::pop_back()
{
	try
	{
		Path_query.pop_back();
		Path_target.pop_back();
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void PathModel::pop_back()" << endl;
	}
}

unsigned int PathModel::size() const
{
	return Path_query.size();
}

pair<long int, long int> PathModel::identity() const
{
	return Path_identity;
}

double PathModel::pvalue() const
{
	return *Path_pvalue;
}

bool PathModel::set() const
{
	return Path_query.size() != 0;
}
