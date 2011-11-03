#include "Hit.hpp"

long long int Hit::Hit_number = 0;

long long int Hit::number()
{
	return Hit_number;
}

Hit::Hit() : HitControler::HitControler()
{
	Hit_number++;
}

Hit::Hit(string const & name, int start, int stop) : HitControler::HitControler(name, start, stop)
{
	Hit_number++;
}

Hit::Hit(int id, string const & name, int start, int stop) : HitControler::HitControler(id, name, start, stop)
{
	Hit_number++;
}

Hit::~Hit()
{
	for(auto & it : Hit_holes)
	{
		delete it;
	}
	Hit_number--;
}

bool Hit::hole(int start, int stop)
{
	if(Hit_start <= start && stop <= Hit_stop)
	{
		for(auto hole : Hit_holes)
		{
			if(hole->over(start, stop))
			{
				return true;
			}
		}
	}
	return false;
}

Hit Hit::operator+(Hit const& Hitbis)
{
	int start, hole_start, stop, hole_stop;
	
	if(Hit_start < Hitbis.start())
		start = Hit_start;
	else
		start = Hitbis.start();
	
	if(Hit_stop < Hitbis.stop())
		stop = Hitbis.stop();
	else
		stop = Hit_stop;
	
	Hit result = Hit(Hit_name, start, stop);
	auto it = Hit_holes.begin();
	auto itbis = Hitbis.Hit_holes.begin();
	
	if(!Hit_holes.empty() || Hitbis.Hit_holes.empty())
	{
		while(it != Hit_holes.end() && itbis != Hitbis.Hit_holes.end())
		{
			while((**itbis) < (**it) && itbis != Hitbis.Hit_holes.end())
			{
				itbis++;
			}
			if((**itbis).in(**it) || (**it).in(**itbis))
			{
				if((**it).start() < (**itbis).start())
					hole_start = (**itbis).start();
				else
					hole_start = (**it).start();
				
				if((**it).stop() < (**itbis).stop())
					hole_stop = (**it).stop();
				else
					hole_stop = (**itbis).stop();
				
				result.add_hole(HitControler("", hole_start, hole_stop));
			}
			it++;
		}
	}
	return result;
}

Hit Hit::operator-(Hit const& Hitbis)
{
	int hole_start = Hit_start;
	int hole_stop;
	
	Hit result = Hit(Hit_name, Hit_start, Hit_stop);
	
	for(auto & it : Hit_holes)
	{
		result.Hit_holes.push_back(new HitControler(*it));
	}
	
	if(!Hit_holes.empty() || Hitbis.Hit_holes.empty())
	{
		for(auto hole: Hitbis.Hit_holes)
		{
			hole_stop = hole->start();
			result.add_hole(new HitControler("", hole_start, hole_stop));
			hole_start = hole->stop();
		}
	}
	
	return result;
}

Hit& Hit::operator+=(Hit const& Hitbis)
{
	int hole_start, hole_stop;
	
	if(Hit_start >= Hitbis.start())
		Hit_start = Hitbis.start();
	
	if(Hit_stop < Hitbis.stop())
		Hit_stop = Hitbis.stop();
	
	auto it = Hit_holes.begin();
	auto itbis = Hitbis.Hit_holes.begin();
	
	if(!Hit_holes.empty() && !Hitbis.Hit_holes.empty())
	{
		while(it != Hit_holes.end() && itbis != Hitbis.Hit_holes.end())
		{
			while((**itbis) < (**it) && itbis != Hitbis.Hit_holes.end())
			{
				itbis++;
			}
			if((**itbis).in(**it) || (**it).in(**itbis))
			{
				if((**it).start() < (**itbis).start())
					hole_start = (**itbis).start();
				else
					hole_start = (**it).start();
				
				if((**it).stop() < (**itbis).stop())
					hole_stop = (**it).stop();
				else
					hole_stop = (**itbis).stop();
				
				add_hole(new HitControler("", hole_start, hole_stop));
			}
			it++;
		}
	}
	else
	{
		if(Hit_holes.empty() && !Hitbis.Hit_holes.empty())
		{
			Hit_holes = Hitbis.Hit_holes;
			for(auto & it : Hitbis.Hit_holes)
			{
				Hit_holes.push_back(new HitControler(*it));
			}
		}
	}
	
	return *this;
}

void Hit::merge(Hit const& hitbis)
{
	if(Hit_start >= hitbis.start())
		Hit_start = hitbis.start();
	
	if(Hit_stop < hitbis.stop())
		Hit_stop = hitbis.stop();
}

bool Hit::neighbor(Hit const& hitbis) const
{
	if(this != &hitbis)
	{
		if(*this <= hitbis)
		{
			if(Hit_name.compare(hitbis.name()) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

Hit& Hit::operator-=(Hit const& Hitbis)
{
	int hole_start = Hit_start;
	int hole_stop;
	
	Hit result = Hit(Hit_name, Hit_start, Hit_stop);
	
	for(auto & it : Hit_holes)
	{
		result.Hit_holes.push_back(new HitControler(*it));
	}
	
	if(!Hit_holes.empty() || Hitbis.Hit_holes.empty())
	{
		for(auto hole: Hitbis.Hit_holes)
		{
			hole_stop = hole->start();
			result.add_hole(HitControler("", hole_start, hole_stop));
			hole_start = hole->stop();
		}
	}
	
	*this = result;
	return *this;
}

bool Hit::operator()(const HitControler* a, const HitControler* b)
{
	return a->start() < b->start();
}

void Hit::sort()
{
	Hit_holes.sort(Hit());
}

void Hit::add_hole(HitControler hole)
{
	if(hole.start() <= Hit_start)
	{
		Hit_start = hole.stop();
	}
	else
	{
		if(Hit_stop <= hole.stop())
		{
			Hit_stop = hole.start();
		}
		else
		{
			try
			{
				Hit_holes.push_back(new HitControler(hole));
				Hit::sort();
			}
			catch(exception const& e)
			{
				cerr << "ERROR : " << e.what() << " in : void Hit::add_hole(HitControler hole)" << endl;
			}
		}
	}
}

void Hit::add_hole(HitControler* hole)
{
	if(hole->start() <= Hit_start)
	{
		Hit_start = hole->stop();
	}
	else
	{
		if(Hit_stop <= hole->stop())
		{
			Hit_stop = hole->start();
		}
		else
		{
			try
			{
				Hit_holes.push_back(hole);
				Hit::sort();
			}
			catch(exception const& e)
			{
				cerr << "ERROR : " << e.what() << " in : void Hit::add_hole(HitControler* hole)" << endl;
			}
		}
	}
}

void Hit::display(ostream &stream) const
{
	stream << Hit_name << "\t";
	if(Hit_sens)
		stream << "+";
	else
		stream << "-";
	stream << "\t" << Hit_start << "\t" << Hit_stop << "\t(" << Hit::size() << ")";
}

ostream &operator<<( ostream &stream, Hit const& h)
{
	h.display(stream);
	return stream;
}
