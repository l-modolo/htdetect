#ifndef DEF_HitView
#define DEF_HitView
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include "HitControler.hpp"

using namespace std;

class Hit : public HitControler
{
	public:
	Hit();
	Hit(string const & name, int start, int stop);
	Hit(int id, string const & name, int start, int stop);
	~Hit();
	
	static long long int number();
	
	bool hole(int start, int stop);
	
	bool operator()(const HitControler* a, const HitControler* b);
	void sort();
	void add_hole(HitControler hole);
	void add_hole(HitControler* hole);
	
	Hit operator+(Hit const& Hitbis);
	Hit operator-(Hit const& Hitbis);
	Hit& operator+=(Hit const& Hitbis);
	Hit& operator-=(Hit const& Hitbis);
	void merge(Hit const& hitbis);
	
	bool neighbor(Hit const&  hitbis) const;
	
	void display(ostream &stream) const;
	
	protected:
	// attribute
	list<HitControler*> Hit_holes;
	static long long int Hit_number;
	
	friend std::ostream& operator<< (std::ostream& flux, Hit const& Hitbis);
};


#endif
