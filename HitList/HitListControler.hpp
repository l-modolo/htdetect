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

#ifndef DEF_HitListControler
#define DEF_HitListControler

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <list>
#include "HitListModel.hpp"

using namespace std;

class HitListControler : public HitListModel
{
	public:
	HitListControler();
	~HitListControler();
	
	bool find(Hit & h) const;
	
	bool operator()(const Hit* a, const Hit* b);
	void sort();
	void remove_overlapping();
	
	void flip_all();
};


#endif
