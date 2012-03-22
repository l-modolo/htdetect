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

#ifndef DEF_PathControler
#define DEF_PathControler

#include "../pTest/pTest.hpp"
#include "PathModel.hpp"

using namespace std;

class PathControler : public PathModel
{
	public:
	PathControler(double chromosome_identity, vector<pair<long int, long int>>* identity, double* pvalue, bool verbose);
	
	void operator()();
	void compute_pvalue();
	
	bool overlapping(PathControler & pathControlerbis);
	bool operator<(PathControler const& pathControlerbis) const;
	bool operator>(PathControler const& pathControlerbis) const;
	bool operator<=(PathControler const& pathControlerbis) const;
	bool operator>=(PathControler const& pathControlerbis) const;
	bool operator==(PathControler const& pathControlerbis) const;
};
#endif

