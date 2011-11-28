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

#include "PathControler.hpp"

PathControler::PathControler(double chromosome_identity, vector<double>* identity, double* pvalue, bool verbose) : PathModel::PathModel(chromosome_identity, identity,pvalue, verbose) {}

void PathControler::compute_pvalue()
{
	try
	{
		if(set())
		{
			Path_size = 0.0;
			double identity_total = 0.0;
			
			for(int i = 0; i< Path_target.size(); i++)
			{
				Path_size += Path_target.at(i)->size();
				identity_total += (Path_target.at(i)->size()) * (Path_hits_identity->at(Path_target.at(i)->id()));
			}
			Path_identity = identity_total/Path_size;
			
			pTest test(Path_chromosome_identity, Path_identity, Path_size, Path_pvalue);
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

void  PathControler::operator()()
{
	compute_pvalue();
}

bool PathControler::overlapping(PathControler const& pathControlerbis) const
{
	return overlapping(pathControlerbis, 0, Path_query.size()),
}

bool PathControler::overlapping(PathControler const& pathControlerbis, int start, int stop) const
{
	if(Path_query.at(0))
	{}
	return true;
}

bool PathControler::operator<(PathControler const& pathControlerbis) const
{
	return *Path_pvalue < *pathControlerbis.Path_pvalue;
}

bool PathControler::operator>(PathControler const& pathControlerbis) const
{
	return *Path_pvalue > *pathControlerbis.Path_pvalue;
}

bool PathControler::operator<=(PathControler const& pathControlerbis) const
{
	return *Path_pvalue <= *pathControlerbis.Path_pvalue;
}

bool PathControler::operator>=(PathControler const& pathControlerbis) const
{
	return *Path_pvalue >= *pathControlerbis.Path_pvalue;
}

bool PathControler::operator==(PathControler const& pathControlerbis) const
{
	return *Path_pvalue == *pathControlerbis.Path_pvalue;
}


