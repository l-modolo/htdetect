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
