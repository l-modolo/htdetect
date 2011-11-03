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

#ifndef DEF_HitListView
#define DEF_HitListView

#include <string>
#include <list>
#include "HitListControler.hpp"

using namespace std;

class HitList : public HitListControler
{
	public:
	HitList();
	~HitList();
	
	HitList operator+(HitList HitListbis);
	HitList& operator+=(HitList HitListbis);
	void merge(HitList & HitListbis);
	
	static int number();
	bool display_hit(ostream &stream, bool last_tab);
	
	protected:
	static int HitList_number;
	void display(ostream &stream) const;
	
	friend std::ostream& operator<< (std::ostream& flux, HitList const& HitListbis);
};


#endif
