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

#include "Sequence.hpp"

Sequence::Sequence(string const & name, long long int start, long long int stop, int line)
{
	try
	{
		if( start >= 0 && stop >= 0)
		{
			if(start < stop)
			{
				Sequence_name = name;
				Sequence_start = start;
				Sequence_stop = stop;
				Sequence_line_size = line;
			}
			else
			{
				throw logic_error("Start position greater than Stop position");
			}
		}
		else
		{
			throw logic_error("Negatives positions");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in Sequence::Sequence(string const & name, long long int start, long long int stop, int line)" << endl;
	}
}

Sequence& Sequence::operator=(Sequence const& Sequencebis)
{
	if(this != &Sequencebis)
	{
		Sequence_name = Sequencebis.Sequence_name;
		Sequence_start = Sequencebis.Sequence_start;
		Sequence_stop = Sequencebis.Sequence_stop;
		Sequence_line_size = Sequencebis.Sequence_line_size;
	}
	return *this;
}

bool Sequence::operator==(Sequence const& Sequencebis) const
{
	if(Sequence_name.compare(Sequencebis.Sequence_name) == 0)
	{
		return true;
	}
	return false;
}

long long int Sequence::start()
{
	return Sequence_start;
}

long long int Sequence::stop()
{
	return Sequence_stop;
}

int Sequence::lines()
{
	return Sequence_line_size;
}

long long int Sequence::size() const
{
	return Sequence_stop-Sequence_start;
}

long long int Sequence::pos(int from) const
{
	try
	{
		if(Sequence_line_size != 0)
		{
			return Sequence_start+from+(from/Sequence_line_size)+1;
		}
		else
		{
			throw logic_error("Can not make a null division");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in long long int Sequence::pos(int from) const" << endl;
		return Sequence_start+from+(from/50)+1;
	}
}

bool Sequence::in(long long int pos) const
{
	if(1 <= pos && pos <= Sequence::size())
	{
		return true;
	}
	return false;
}

void Sequence::display(ostream &stream) const
{
	stream << Sequence_name << "\t" << Sequence_start  << "\t" << Sequence_stop << "\t" << Sequence::size();
}

ostream &operator<<( ostream &stream, Sequence const&s)
{
	s.display(stream);
	return stream;
}


