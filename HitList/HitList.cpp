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


