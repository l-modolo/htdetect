/*
htdetect horizontal transfert detection tools
Copyright (C) 2011  Laurent Modolo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DEF_HitModel
#define DEF_HitModel

#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <map>
#include <mutex>
#include <vector>

using namespace std;

class HitModel {
	public:
	HitModel();
	HitModel(string const & name, int start, int stop);
	HitModel(int id, string const & name, int start, int stop);
	HitModel(HitModel const& Hitbis);
	HitModel& operator=(HitModel const& Hitbis);

	int id() const;
	void set_id(int id);
	bool sens() const;
	int start() const;
	int stop() const;
	string name() const;
	bool set() const;

	void set_attr(int key, int value);
	int get_attr(int key);

	protected:
	// attributes
	int Hit_id;
	bool Hit_sens;
	int Hit_name;
	int Hit_start;
	int Hit_stop;
	vector<int> Hit_attr;

	static mutex Hit_names_lock;
	static map<unsigned int, string> Hit_id_names;
	static map<string, unsigned int> Hit_names_id;

	private:
	void init(int id, string const & name, int start, int stop);

	unsigned int add_name(string name);
};


#endif

