/*
getseq tools to build a fasta file from a blast or htdetect output
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
	string htdetect;
	string blast;
	string fasta1;
	string fasta2;
	string restore;
	int steptosave = 0;
	int thread_number = 10;
	double chromosome_identity = -1.0;
	string tmp_rep = "/tmp";
	string output;
	bool verbose = false;
	
	static struct option long_options[] =
	{
		{"blast", required_argument, 0, 'a'},
		{"fasta1", required_argument, 0, 'b'},
		{"fasta2", required_argument, 0, 'c'},
		{"n", required_argument, 0, 'd'},
		{"tmp", required_argument, 0, 'e'},
		{"identity", required_argument, 0, 'f'},
		{"htdetect", required_argument, 0, 'g'},
		{"output", required_argument, 0, 'o'},
		{"v", 0, 0, 'r'},
		{0, 0, 0, 0}
	};
	
	while ((c = getopt_long_only (argc, argv, "a:b:c:d:e:f:o:p:q:r:", long_options, &option_index)) != -1) {
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
			case 'g':
				htdetect = optarg;
				cout << "htdetect file : " << htdetect << endl;
			break;
			case 'o':
				output = optarg;
				cout << "output : " << output << endl;
			break;
			case 'r':
				verbose = true;
				cout << "verbose enable" << endl;
			break;
			case ':':
				cout << "without argument : " << optopt << endl;
			break;
			case '?':
			break;
		}
	}
	
	// the only required argument is the blast file
	if((blast.empty() && htdetect.empty()) || fasta1.empty() || fasta2.empty() || output.empty()){
		cout << "Argument must be defined." << endl;
		cout << "Usage: getset [--blast <blast_file -m8> || --htdetect <htdetect_file>] --fasta1 <fasta_file> --fasta2 <fasta_file> --output <output_file>" << endl;
		cout << "       --fasta1 the subject species (the best assembled one)" << endl;
		cout << "       --fasta2 the target species (the worst assembled one)" << endl;
		cout << "Optional:" << endl;
		cout << "       --identity <chromosome identity> compute p-value of thes hits according to an identity ceil" << endl;
		cout << "       --v enable verbose mode (htdetect says what he is doing)" << endl;
		return 1;
	}
	
	int step = 0;
	
	cout << "oppening : " << fasta1 << endl;
	Fasta f1(fasta1);
	cout << "oppening : " << fasta2 << endl;
	Fasta f2(fasta2);
	
	if(htdetect.empty())
	{
		cout << "oppening : " << blast << endl;
		Blast b(verbose);
		b.load(output, blast, &f1, &f2);
		cout << "writting : " << output << endl;
		b.toFasta(output, thread_number, tmp_rep);
	}
	else
	{
		cout << "oppening: " << htdetect << endl;
		Blast b(verbose);
		b.restore(output, htdetect, &f1, &f2);
		cout << "writting : " << output << endl;
		b.toFasta(output, thread_number, tmp_rep);
	}
	
	return 0;
}
