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

#ifndef DEF_AlignementGet
#define DEF_AlignementGet

#include "Alignement.hpp"

using namespace std;

class AlignementGet : public Alignement {
	public:
	AlignementGet(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, vector<double>* identity, string* muscle_path, int thread_id, string* tmp_rep);
	
	AlignementGet& operator=(AlignementGet const& alignementbis);
	
	void operator()();
	void operator()(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, vector<double>* identity, string* muscle_path, int thread_id, string* tmp_rep);
	
	protected:
	void run();
	
	vector<double>* Alignement_identity;
	
	private:
	double compute_identity(bool reverse);
};


#endif
