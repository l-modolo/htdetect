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

#ifndef DEF_PathView
#define DEF_PathView


#include "PathControler.hpp"

using namespace std;

class Path : public PathControler
{
	public:
	Path(double chromosome_identity, vector<double>* identity, double* pvalue, bool verbose);
	~Path();
	
	static int number();
	
	protected:
	static int Path_number;
};

#endif

