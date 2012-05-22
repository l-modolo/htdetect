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

#include "PathThread.hpp"

PathThread::PathThread(Path data)
{
	Path_query = data.Path_query;
	Path_target = data.Path_target;
	
	Path_identity = data.Path_identity;
	Path_pvalue = data.Path_pvalue;
	
	Path_chromosome_identity = data.Path_chromosome_identity;
	Path_hits_identity = data.Path_hits_identity;
}

void PathThread::compute_pvalue()
{
	try
	{
		if(Path_query.size() != 0)
		{
			// as we already have the identity and the size of each hit in the path
			// we can easylly compute the p-value for the whole path
			double Path_size = 0.0;
			pair<long int, long int> identity_total(0,0);
			
			for(int i = 0; i< Path_target.size(); i++)
			{
				Path_size += Path_target.at(i)->size();
				identity_total.first += (Path_hits_identity->at(Path_target.at(i)->id())).first;
				identity_total.second += (Path_hits_identity->at(Path_target.at(i)->id())).second;
			}
			
			pTest test(Path_chromosome_identity, identity_total, Path_size, Path_pvalue);
			test();
		}
		else
			throw logic_error("Path is empty");
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void PathControler::compute_pvalue()" << endl;
	}
}

void  PathThread::operator()()
{
	compute_pvalue();
}
