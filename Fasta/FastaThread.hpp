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

#ifndef DEF_FastaThread
#define DEF_FastaThread

#include "../Hit/Hit.hpp"
#include "Fasta.hpp"

using namespace std;

class FastaThread
{
	public:
//	FastaThread(Fasta * fasta, Hit * hit);
	FastaThread(Fasta fasta, Hit hit);
//	~FastaThread();
	
	string* find();
	string* operator()();
	
	private:
	Sequence findSeq();
	
	Fasta FastaThread_fasta;
	Hit FastaThread_hit;
	
	static mutex FastaThread_onebyone;
};

#endif
