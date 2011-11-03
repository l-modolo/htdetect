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

#include "HitList.hpp"

int HitList::HitList_number = 0;

int HitList::number()
{
	return HitList_number;
}

HitList::HitList() : HitListControler::HitListControler()
{
	HitList_number++;
}

HitList::~HitList()
{
	HitList_number--;
}

HitList HitList::operator+(HitList HitListbis)
{
	HitList result(*this);
	for(int i = 0; i < HitListbis.size(); i++)
	{
		result.add_hit(*HitListbis.hit(i));
	}
	return result;
}

HitList& HitList::operator+=(HitList HitListbis)
{
	for(int i = 0; i < HitListbis.size(); i++)
	{
		add_hit(*HitListbis.hit(i));
	}
	sort();
	return *this;
}

void HitList::merge(HitList & HitListbis)
{
	try
	{
		if(HitListbis.size() < 1)
		{
			throw logic_error("HitListbis is empty");
		}
		for(int i = 0; i < HitListbis.size(); i++)
		{
			add_hit(HitListbis.hit(i));
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << "in : void HitList::merge(HitList* & HitListbis)" << endl;
	}
}

void HitList::display(ostream &stream) const
{
	for(auto & h : HitList_hits)
	{
		stream << "\t" << *h << endl;
	}
}

ostream &operator<<( ostream &stream, HitList const& hl)
{
	hl.display(stream);
	return stream;
}


