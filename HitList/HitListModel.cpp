#include "HitListModel.hpp"

HitListModel::HitListModel()
{
	
}

HitListModel::~HitListModel()
{
	for(auto & it : HitList_hits)
	{
		delete it;
	}
}

HitListModel::HitListModel(HitListModel const& HitListbis)
{
	for(auto & it : HitListbis.HitList_hits)
	{
		HitList_hits.push_back(new Hit(*it));
	}
}

HitListModel& HitListModel::operator=(HitListModel const& HitListbis)
{
	if(this != &HitListbis)
	{
		for(auto & it : HitListbis.HitList_hits)
		{
			HitList_hits.push_back(new Hit(*it));
		}
	}
	return *this;
}

int HitListModel::size() const
{
	return HitList_hits.size();
}

Hit* HitListModel::hit(int i)
{
	try
	{
		return HitList_hits.at(i);
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in Hit* HitListModel::hit(int i)" << endl;
		return *HitList_hits.begin();
	}
}

Hit* HitListModel::last_hit()
{
	return HitList_hits.back();
}

void HitListModel::add_hit(Hit & hitbis)
{
	try
	{
		HitList_hits.push_back(new Hit(hitbis));
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void HitListModel::add_hit(Hit & hitbis)" << endl;
	}
}

void HitListModel::add_hit(Hit* hitbis)
{
	try
	{
		HitList_hits.push_back(hitbis);
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void HitListModel::add_hit(Hit* hitbis)" << endl;
	}
}

void HitListModel::add_hit(string const & name, int start, int stop)
{
	HitList_hits.push_back(new Hit(HitList_hits.size(), name, start, stop));
}

void HitListModel::add_hit(int id, string const & name, int start, int stop)
{
	HitList_hits.push_back(new Hit(id, name, start, stop));
}

void HitListModel::add_hit(string const & name, int start, int stop, list<int> holes)
{
	try
	{
		if(holes.size()%2 == 0)
		{
			Hit* new_Hit = new Hit(HitList_hits.size(), name, start, stop);
			int hole_start, hole_stop;
			auto it = holes.begin();
			while(it != holes.end())
			{
				hole_start = *it;
				it++;
				hole_stop = *it;
				new_Hit->add_hole(HitControler("", hole_start, hole_stop));
			}
			
			HitList_hits.push_back(new_Hit);
		}
		else
		{
			throw logic_error("holes list size is not a multiple of 2, eatch holes needs to have a start and end position");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in void HitListModel::add_hit(string const & name, int start, int stop, list<int> holes)" << endl;
	}
}

void HitListModel::clear()
{
	for(auto & it : HitList_hits)
	{
		delete it;
		it = nullptr;
	}
	HitList_hits.clear();
}

void HitListModel::clear_nodelete()
{
	for(auto & it : HitList_hits)
	{
		it = nullptr;
	}
	HitList_hits.clear();
}

