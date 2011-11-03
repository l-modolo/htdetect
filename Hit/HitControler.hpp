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

#ifndef DEF_HitControler
#define DEF_HitControler
#include <fstream>
#include <string>
#include <iostream>
#include "HitModel.hpp"

using namespace std;

class HitControler : public HitModel
{
	public:
	HitControler();
	HitControler(string const & name, int start, int stop);
	HitControler(int id, string const & name, int start, int stop);
	
	int size() const;
	
	bool operator<(HitControler const& Hitbis) const;
	bool operator>(HitControler const& Hitbis) const;
	bool operator<=(HitControler const& Hitbis) const;
	bool operator>=(HitControler const& Hitbis) const;
	bool operator==(HitControler const& Hitbis) const;
	bool operator==(HitControler* const& Hitbis) const;
	bool operator!=(HitControler const& Hitbis) const;
	bool in(HitControler const& Hitbis) const;
	bool over(HitControler const& Hitbis) const;
	bool over(int start, int stop) const;
};


#endif
