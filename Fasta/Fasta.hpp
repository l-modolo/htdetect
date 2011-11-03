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

#ifndef DEF_Fasta
#define DEF_Fasta

#include "FastaControler.hpp"

using namespace std;

class FastaThread;

class Fasta : public FastaControler
{
	public:
	Fasta(string const & file);
	
	private:
	void display(ostream &stream) const;
	
	friend std::ostream& operator<< (std::ostream& flux, Fasta const& Fastabis);
	friend class FastaThread;
};

#endif
