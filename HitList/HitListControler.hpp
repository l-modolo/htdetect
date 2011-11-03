#ifndef DEF_HitListControler
#define DEF_HitListControler

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <list>
#include "HitListModel.hpp"

using namespace std;

class HitListControler : public HitListModel
{
	public:
	HitListControler();
	
	bool find(Hit & h) const;
	
	bool operator()(const Hit* a, const Hit* b);
	void sort();
	void remove_overlapping();
};


#endif
