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

#include <iostream>
#include "Hit/Hit.hpp"
#include "HitList/HitList.hpp"
#include "Blast/Blast.hpp"
#include "Fasta/Fasta.hpp"
#include <getopt.h>

int main(int argc, char *argv[]) {
	// getting the parametters
	int c;
	int option_index = 0;
	string blast;
	string fasta1;
	string fasta2;
	string restore;
	int steptosave = 0;
	int thread_number = 50;
	double chromosome_identity = -1.0;
	string tmp_rep = "/tmp";
	string output;
	
	static struct option long_options[] =
	{
		{"blast", required_argument, 0, 'a'},
		{"fasta1", required_argument, 0, 'b'},
		{"fasta2", required_argument, 0, 'c'},
		{"n", required_argument, 0, 'd'},
		{"tmp", required_argument, 0, 'e'},
		{"identity", required_argument, 0, 'f'},
		{"output", required_argument, 0, 'o'},
		{"restore", required_argument, 0, 'p'},
		{"sav", required_argument, 0, 'q'},
		{0, 0, 0, 0}
	};
	
	while ((c = getopt_long_only (argc, argv, "a:b:c:d:e:f:o:p:q:", long_options, &option_index)) != -1) {
		switch(c) {
			case 'a':
				blast = optarg;
				cout << "blast file : " << blast << endl;
			break;
			case 'b':
				fasta1 = optarg;
				cout << "fasta 1 file : " << fasta1 << endl;
			break;
			case 'c':
				fasta2 = optarg;
				cout << "fasta 2 file : " << fasta2 << endl;
			break;
			case 'd':
				thread_number = atoi(optarg);
				cout << "thread number : " << thread_number << endl;
			break;
			case 'e':
				tmp_rep = optarg;
				cout << "tmp file : " << tmp_rep << endl;
			break;
			case 'f':
				chromosome_identity = atof(optarg);
				cout << "chromosome identity : " << chromosome_identity << endl;
			break;
			case 'o':
				output = optarg;
				cout << "output : " << output << endl;
			break;
			case 'p':
				restore = optarg;
				cout << "restore from : " << output << endl;
			break;
			case 'q':
				steptosave = atoi(optarg);
				cout << "step to save : " << output << endl;
			break;
			case ':':
				cout << "without argument : " << optopt << endl;
			break;
			case '?':
			break;
		}
	}
	
	// the only required argument is the blast file
	if(blast.empty() || fasta1.empty() || fasta2.empty() || output.empty()){
		cout << "Argument must be defined." << endl;
		cout << "Usage: htdetect --blast <blast_file -m8> --fasta1 <fasta_file> --fasta2 <fasta_file> --output <output_file> --identity <chromosome identity>" << endl;
		cout << "       --fasta1 the subject species (the best assembled one)" << endl;
		cout << "       --fasta2 the target species (the worst assembled one)" << endl;
		cout << "Optional:" << endl;
		cout << "       --restore a .sav file to restore data from a previous execution" << endl;
		cout << "       --sav step to create the .sav" << endl;
		return 1;
	}
	
	int step = 0;
	
	cout << "oppening : " << fasta1 << endl;
	Fasta f1(fasta1);
	cout << "oppening : " << fasta2 << endl;
	Fasta f2(fasta2);
	cout << "oppening : " << blast << endl;
	
	Blast b;
	if(restore.empty())
		b.load(output, blast, &f1, &f2);
	else
		b.restore(restore, &f1, &f2);
	
	b.remove_overlapping();
	step++;
	if(steptosave == step)
		b.sav();
	
	b.compute_identity(thread_number, tmp_rep);
	step++;
	if(steptosave == step)
		b.sav();
	
	if(chromosome_identity >= 0.0)
	{
		b.compute_test(chromosome_identity, thread_number);
		step++;
		if(steptosave == step)
			b.sav();
	}
	
	cout << "writing " << output << "..." << endl;
	
	ofstream outputf(output);
	try
	{
		if(outputf)
		{
			outputf << b << endl;
		}
		else
		{
			throw logic_error("Can not open "+output);
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << endl;
	}
	outputf.close();
	
	return 0;
}
