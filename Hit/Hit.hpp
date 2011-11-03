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

#ifndef DEF_HitView
#define DEF_HitView
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include "HitControler.hpp"

using namespace std;

class Hit : public HitControler
{
	public:
	Hit();
	Hit(string const & name, int start, int stop);
	Hit(int id, string const & name, int start, int stop);
	~Hit();
	
	static long long int number();
	
	bool hole(int start, int stop);
	
	bool operator()(const HitControler* a, const HitControler* b);
	void sort();
	void add_hole(HitControler hole);
	void add_hole(HitControler* hole);
	
	Hit operator+(Hit const& Hitbis);
	Hit operator-(Hit const& Hitbis);
	Hit& operator+=(Hit const& Hitbis);
	Hit& operator-=(Hit const& Hitbis);
	void merge(Hit const& hitbis);
	
	bool neighbor(Hit const&  hitbis) const;
	
	void display(ostream &stream) const;
	
	protected:
	// attribute
	list<HitControler*> Hit_holes;
	static long long int Hit_number;
	
	friend std::ostream& operator<< (std::ostream& flux, Hit const& Hitbis);
};


#endif
