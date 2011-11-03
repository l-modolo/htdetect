#ifndef DEF_HitModel
#define DEF_HitModel

#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

class HitModel {
	public:
	HitModel();
	HitModel(string const & name, int start, int stop);
	HitModel(int id, string const & name, int start, int stop);
	HitModel(HitModel const& Hitbis);
	HitModel& operator=(HitModel const& Hitbis);
	
	int id() const;
	bool sens() const;
	int start() const;
	int stop() const;
	string name() const;
	
	protected:
	// attributes
	int Hit_id;
	bool Hit_sens;
	string Hit_name;
	int Hit_start;
	int Hit_stop;
	
	private:
	void init(int id, string const & name, int start, int stop);
};


#endif
