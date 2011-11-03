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

#ifndef DEF_BlastView
#define DEF_BlastView
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "BlastControler.hpp"

using namespace std;

class Blast : public BlastControler
{
	public:
	Blast();
	Blast(string const & name, string const & file);
	Blast(string const & name, string const & file, Fasta* fasta);
	Blast(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2);
	Blast(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2, string const & muscle_path);
	~Blast();
	
	static int number();
	
	protected:
	static int Blast_number;
	void display(ostream &stream);
	
	friend std::ostream& operator<< (std::ostream& flux, Blast &hitbis);
};

#endif

