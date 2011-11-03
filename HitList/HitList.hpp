#ifndef DEF_HitListView
#define DEF_HitListView

#include <string>
#include <list>
#include "HitListControler.hpp"

using namespace std;

class HitList : public HitListControler
{
	public:
	HitList();
	~HitList();
	
	HitList operator+(HitList HitListbis);
	HitList& operator+=(HitList HitListbis);
	void merge(HitList & HitListbis);
	
	static int number();
	bool display_hit(ostream &stream, bool last_tab);
	
	protected:
	static int HitList_number;
	void display(ostream &stream) const;
	
	friend std::ostream& operator<< (std::ostream& flux, HitList const& HitListbis);
};


#endif
