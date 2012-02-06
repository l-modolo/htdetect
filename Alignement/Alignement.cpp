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

#include "Alignement.hpp"

string salt()
{
	char charArray[] = {
	'A','B','C','D','E','F','G','H','I',
	'J','K','L','M','N','O','P','Q','R',
	'S','T','U','V','W','X','Y','Z','a',
	'b','c','d','e','f','g','h','i','j',
	'k','l','m','n','o','p','q','r','s',
	't','u','v','w','x','y','z','1','2',
	'3','4','5','6','7','8','9','0'};
	srand(time(NULL));
	string salt;
	
	for(int i=0; i<10; i++)
	{
		salt.push_back(charArray[rand() % 62]);
	}
	return salt;
}

string Alignement::Alignement_salt = salt();

int Alignement::number()
{
	return Alignement_id;
}

Alignement::Alignement(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, string* muscle_path, int thread_id , string* tmp_rep)
{
	Alignement_fasta_a = fasta_a;
	Alignement_fasta_b = fasta_b;
	Alignement_hit_a = hit_a;
	Alignement_hit_b = hit_b;
	
	Alignement_path = muscle_path;
	Alignement_tmp_rep = tmp_rep;
	
	Alignement_id = thread_id;
	
	Alignement_init = false;
}

void Alignement::align()
{
	string in, out;
	stringstream ss;
	ss << Alignement::number();
	in = *Alignement_tmp_rep+"/htdetect."+Alignement_salt+"."+ss.str()+".pir";
	out = *Alignement_tmp_rep+"/htdetect"+Alignement_salt+"."+ss.str()+".out";
	ofstream outputf(in);
	try
	{
		if(outputf)
		{
			outputf << ">a" << endl << *Alignement_first_seq << endl;
			outputf << ">b" << endl << *Alignement_second_seq << endl;
			outputf.close();
			
			string cmd = *Alignement_path+" -quiet -in "+in+" -out "+out;
			system(cmd.c_str());
			
			if(remove(in.c_str()) != 0 )
				throw logic_error("Can not remove "+in);
			
			Alignement::read(&out);
			
			if(remove(out.c_str()) != 0 )
				throw logic_error("Can not remove "+out);
		}
		else
		{
			throw logic_error("Can not open "+in);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in void Alignement::align()" << endl;
		cerr << ">" << *Alignement_first_seq << endl;
		cerr << ">" << *Alignement_second_seq << endl;
		outputf.close();
		exit(-1);
	}
}

void Alignement::read(string* Fasta_file)
{
	ifstream fFasta(*Fasta_file);
	
	if(fFasta)
	{
		Alignement_first_seq->clear();
		Alignement_second_seq->clear();
		
		string line, header;
		bool first = true;
		
		while(getline(fFasta, line))
		{
			if(line[0] == '>')
			{
				if(!header.empty())
				{
					first = false;
				}
				header = line;
			}
			else
			{
				if(line.length() != 0)
				{
					if(first)
						Alignement_first_seq->append(line);
					else
						Alignement_second_seq->append(line);
				}
			}
		}
		fFasta.close();
	}
	else
	{
		fFasta.close();
		throw logic_error("Can not open file : "+(*Fasta_file)+" in void Alignement::read(string* Fasta_file)");
	}
}

void Alignement::complementary(string * seq)
{
	for(size_t i=0; i < seq->length(); i++)
	{
		switch(tolower(seq->at(i)))
		{
			case 'a':
			seq->at(i) = 'T';
			break;
			
			case 't':
			seq->at(i) = 'A';
			break;
			
			case 'c':
			seq->at(i) = 'G';
			break;
			
			case 'g':
			seq->at(i) = 'C';
			break;
		}
	}
}
