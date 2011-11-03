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

#include "FastaControler.hpp"

FastaControler::FastaControler(string const & file) : FastaModel::FastaModel(file) {}

Sequence* FastaControler::findSeq(string const & header)
{
	auto it = std::find(Fasta_sequences.begin(), Fasta_sequences.end(), Sequence(header, 0, 10, 0));
	try{
		if(it == Fasta_sequences.end())
		{
			throw logic_error("Sequence not found : "+header+" in file "+Fasta_file);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in Sequence* FastaControler::findSeq(string const & header)" << endl;
	}
	return &(*it);
}

string FastaControler::find(string const & header)
{
	Sequence* s = findSeq(header);
	string seq;
	try
	{
		ifstream fFasta(Fasta_file);
		
		if(fFasta)
		{
			fFasta.seekg(s->start());
			char currentchar = fFasta.get();
			while(fFasta.tellg() < s->stop())
			{
				if(currentchar != '\n' && currentchar != '\r' && currentchar != EOF)
					seq.push_back(currentchar);
				currentchar = fFasta.get();
			}
			fFasta.close();
		}
		else
		{
			throw logic_error("Can not open file : "+Fasta_file);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in string FastaControler::find(string const & header)"<< endl;
	}
	return seq;
}

string FastaControler::find(string const & header, long long int start, long long int stop)
{
	Sequence* s = findSeq(header);
	string seq;
	if(s->stop() < s->pos(stop))
	{
		stop = s->stop();
	}
	else
	{
		stop = s->pos(stop);
	}
	
	try
	{
		ifstream fFasta(Fasta_file);
		
		if(fFasta)
		{
			fFasta.seekg(s->pos(start));
			char currentchar = fFasta.get();
			
			while(fFasta.tellg() < stop)
			{
				if(currentchar != '\n' && currentchar != '\r' && currentchar != EOF)
					seq.push_back(currentchar);
				currentchar = fFasta.get();
			}
			fFasta.close();
		}
		else
		{
			throw logic_error("Can not open file : "+Fasta_file);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in string FastaControler::find(string const & header, long long int start, long long int stop)" << endl;
	}
	return seq;
}

string FastaControler::find(string const & header, long long int start, long long int stop, bool reverse)
{
	string seq = find(header, start, stop);
	if(reverse)
	{
		std::reverse(seq.begin(),seq.end());
	}
	return seq;
}
