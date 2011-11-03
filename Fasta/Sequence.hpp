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

#ifndef DEF_Sequence
#define DEF_Sequence

#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>

using namespace std;

class Sequence {
	public:
	Sequence(string const & name, long long int start, long long int stop, int line);
	
	bool operator==(Sequence const& Sequencebis) const;
	
	long long int start();
	long long int stop();
	int lines();
	
	long long int size() const;
	long long int pos(int from) const;
	bool in(long long int pos) const;
	
	protected:
	// attributes
	string Sequence_name;
	long long int Sequence_start;
	long long int Sequence_stop;
	int Sequence_line_size;
	
	private:
	void display(ostream &stream) const;
	
	friend std::ostream& operator<< (std::ostream& flux, Sequence const&s);
};


#endif
