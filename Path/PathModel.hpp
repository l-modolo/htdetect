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
	PathModel(Fasta* fasta_a, Fasta* fasta_b, string muscle_path, bool verbose);
	~PathModel();
	
	void add(Hit* hit_query, Hit* hit_target);
	pair<Hit*, Hit*> operator[](int i);
	
	unsigned int size() const;
	double identity() const;
	double pvalue() const;
	
	bool set() const;
	
	protected:
	
	Fasta* Path_fasta_a;
	Fasta* Path_fasta_b;
	string Path_muscle_path;
	bool Path_verbose;
	
	vector<Hit*> Path_query;
	vector<Hit*> Path_target;
	
	unsigned int Path_size;
	double Path_identity;
	double Path_pvalue;
	
	friend class Alignement;
};

#endif

