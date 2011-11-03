#include "HitListControler.hpp"

HitListControler::HitListControler() : HitListModel::HitListModel() {}

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
		map<string, list<Hit*>* > by_chromo;
		try
		{
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
					if((*hit)->over(**hit_next))
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
		}
		catch(exception const& e)
		{
			cerr << "ERROR : " << e.what() << " in void HitListControler::remove_overlapping()" << endl;
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
}


