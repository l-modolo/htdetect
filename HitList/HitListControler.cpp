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

#include "HitListControler.hpp"

HitListControler::HitListControler() : HitListModel::HitListModel() {}
HitListControler::~HitListControler() {}

bool HitListControler::find(Hit & h) const
{
	for(auto & it : HitList_hits)
	{
		if(h == *it)
			return true;
	}
	return false;
}

bool HitListControler::operator()(const Hit* a, const Hit* b)
{
	return a->start() <= b->start();
}

void HitListControler::sort()
{
	std::stable_sort(HitList_hits.begin(), HitList_hits.end(), HitListControler());
}

void HitListControler::remove_overlapping()
{
	if(size() > 1)
	{
		try
		{
			map<string, list<Hit*>* > by_chromo;
			
			for(auto & it : HitList_hits)
			{
				if(by_chromo.find(it->name()) == by_chromo.end())
					by_chromo[it->name()] = new list<Hit*>;
				by_chromo.find(it->name())->second->push_back(it);
			}
			clear_nodelete();
			
			list<Hit*>::iterator hit, hit_next;
			for(auto it=by_chromo.begin(); it != by_chromo.end(); it++ )
			{
				(*it).second->sort(HitListControler());
				hit = it->second->begin();
				hit_next = hit;
				hit_next++;
				while(hit != (*it).second->end() && hit_next != (*it).second->end())
				{
					if((*hit)->over(**hit_next) && (*hit)->sens() == (*hit_next)->sens())
					{
						(*hit)->merge(**hit_next);
						delete *hit_next;
						*hit_next = nullptr;
						hit_next = (*it).second->erase(hit_next);
					}
					else
					{
						hit++;
						hit_next++;
					}
				}
			}
			for(auto & it : by_chromo)
			{
				for(auto & itbis : *(it.second))
				{
					if(itbis != nullptr)
					{
						add_hit(itbis);
						itbis = nullptr;
					}
				}
				delete it.second;
			}
		}
		catch(exception const& e)
		{
			cerr << "ERROR : " << e.what() << " in void HitListControler::remove_overlapping()" << endl;
		}
	}
}

void HitListControler::flip_all()
{
	for(auto & it : HitList_hits)
	{
		it->flip();
	}
}


