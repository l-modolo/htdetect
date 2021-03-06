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

#ifndef DEF_PathModel
#define DEF_PathModel

#include <utility>
#include "../Hit/Hit.hpp"
#include "../Fasta/Fasta.hpp"
#include "../ProgressBar/ProgressBar.hpp"

using namespace std;

class PathModel
{
	public:
	PathModel(double chromosome_identity, vector<pair<long int, long int>>* identity, double* pvalue, bool verbose);
	~PathModel();
	PathModel& operator=(PathModel const& pathModelbis);
	
	bool test(Hit* hit_query, Hit* hit_target);
	void add(Hit* hit_query, Hit* hit_target);
	pair<Hit*, Hit*> operator[](int i);
	pair<Hit*, Hit*> at(int i);
	
	Hit* target_hit(int id);
	
	unsigned int size() const;
	pair<long int, long int> identity() const;
	double pvalue() const;
	
	bool set() const;
	
	bool rm_front(int query_id);
	bool rm_back(int query_id);
	
	protected:
	void pop_front();
	void pop_back();
	
	bool Path_verbose;
	
	vector<Hit*> Path_query;
	vector<Hit*> Path_target;
	
	unsigned int Path_size;
	pair<long int, long int> Path_identity;
	double* Path_pvalue;
	
	double Path_chromosome_identity;
	vector<pair<long int, long int>>* Path_hits_identity;
	
	static int Path_error;
	
	friend class pTest;
};

#endif

