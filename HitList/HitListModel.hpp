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

#ifndef DEF_HitListModel
#define DEF_HitListModel

#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "../Hit/Hit.hpp"

using namespace std;

class HitListModel {
	public:
	HitListModel();
	HitListModel(HitListModel const& HitListbis);
	HitListModel& operator=(HitListModel const& HitListbis);
	~HitListModel();
	
	void add_hit(string const & name, int start, int stop);
	void add_hit(Hit & hitbis);
	void add_hit(Hit* hitbis);
	void add_hit(int id, string const & name, int start, int stop);
	void add_hit(string const & name, int start, int stop, list<int> holes);
	
	int size() const;
	Hit* hit(int i);
	Hit* last_hit();
	
	void clear();
	void clear_nodelete();
	
	protected:
	// attributes
	vector<Hit*> HitList_hits;
	
	private:
	void init();
};


#endif
