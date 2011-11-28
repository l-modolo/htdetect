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

#include "FastaModel.hpp"

FastaModel::FastaModel(string const & file)
{
	Fasta_file = file;
	try
	{
		ifstream fFasta(Fasta_file);
		
		if(fFasta)
		{
			int start = -1;
			int stop = -1;
			int line_size = 0;
			string line, header;
			while(getline(fFasta, line))
			{
				if(line[0] == '>')
				{
					if(stop != -1 && line_size != 0)
					{
						Fasta_sequences.push_back(Sequence(header.substr((size_t)1,header.find_first_of(" ")-1), start, stop, line_size));
					}
					start = fFasta.tellg();
					header = line;
				}
				else
				{
					if(line.length() != 0 && line_size == 0)
					{
						line_size = line.length();
					}
				}
				stop = fFasta.tellg();
			}
			Fasta_sequences.push_back(Sequence(header.substr((size_t)1,header.find_first_of(" ")-1), start, stop, line_size));
			fFasta.close();
		}
		else
		{
			throw logic_error("Can not open file : "+Fasta_file);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in FastaModel::FastaModel(string const & file)" << endl;
	}
}

FastaModel& FastaModel::operator=(FastaModel const& Fastabis)
{
	if(this != &Fastabis)
	{
		Fasta_file = Fastabis.Fasta_file;
		Fasta_sequences = Fastabis.Fasta_sequences;
	}
	return *this;
}
