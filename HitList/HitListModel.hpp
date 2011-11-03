#ifndef DEF_HitListModel
#define DEF_HitListModel

#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "../Hit/Hit.hpp"

using namespace std;

class HitListModel {
	public:
	HitListModel();
	HitListModel(HitListModel const& HitListbis);
	HitListModel& operator=(HitListModel const& HitListbis);
	~HitListModel();
	
	void add_hit(string const & name, int start, int stop);
	void add_hit(Hit & hitbis);
	void add_hit(Hit* hitbis);
	void add_hit(int id, string const & name, int start, int stop);
	void add_hit(string const & name, int start, int stop, list<int> holes);
	
	int size() const;
	Hit* hit(int i);
	Hit* last_hit();
	
	void clear();
	void clear_nodelete();
	
	protected:
	// attributes
	vector<Hit*> HitList_hits;
	
	private:
	void init();
};


#endif
