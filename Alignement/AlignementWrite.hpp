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

#ifndef DEF_AlignementWrite
#define DEF_AlignementWrite

#include "Alignement.hpp"

using namespace std;

class AlignementWrite : public Alignement{
	public:
	AlignementWrite(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, string* first_seq, string* second_seq, string* muscle_path, int thread_id , string* tmp_rep, mutex* controler);
	
	AlignementWrite& operator=(AlignementWrite const& alignementbis);
	
	void operator()();
	
	protected:
	void run();
	
	mutex* Alignement_controler;
	
	private:
	void trunquate_sequence();
	
	friend class writeSeq;
};


#endif
