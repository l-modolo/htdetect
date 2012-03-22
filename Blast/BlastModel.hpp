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

#ifndef DEF_BlastModel
#define DEF_BlastModel
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <utility>
#include <array>
#include <cstring>
#include "../HitList/HitList.hpp"
#include "../Fasta/Fasta.hpp"
#include "../ProgressBar/ProgressBar.hpp"
#include "../Alignement/AlignementGet.hpp"
#include "../Alignement/AlignementWrite.hpp"
#include "../pTest/pTest.hpp"
#include "../mThread/mThread.hpp"
#include "../PathWalker/PathWalker.hpp"

using namespace std;

class BlastModel
{
	public:
	BlastModel(bool verbose);
	BlastModel(BlastModel & Blastbis);
	~BlastModel();
	
	void sav();
	void restore(string const & file, Fasta* fasta_a, Fasta* fasta_b);
	void restore(string const & name, string const & file, Fasta* fasta_a, Fasta* fasta_b);
	void load(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2);
	
	string name() const;
	string file() const;
	int size() const;
	
	Hit* hit_query(int i);
	Hit* hit_target(int i, int j);
	HitList* target(int i);
	
	int hit_target_size(int i);
	pair<long int, long int> identity(int i, int j);
	double pvalue(int i, int j);
	double statistic(int i, int j);
	bool neighbor_prev(int i, int j);
	bool neighbor_next(int i, int j);
	
	void set_pvalue(int i, int j, double value);
	void set_statistic(int i, int j, double value);
	void set_neighbor_prev(int i, int j, bool value);
	void set_neighbor_next(int i, int j, bool value);
	
	protected:
	void read();
	vector<string> split(string const & str, char * spliter);
	
	Fasta* Blast_fasta_a;
	Fasta* Blast_fasta_b;
	string Blast_muscle_path;
	string Blast_file;
	string Blast_name;
	bool Blast_verbose;
	
	HitList Blast_query;
	vector<HitList*> Blast_target;
	
	vector<bool> Blast_neighbor_prev;
	vector<bool> Blast_neighbor_next;
	vector<pair<long int, long int>> Blast_identity;
	vector<double> Blast_pvalue;
	vector<double> Blast_statistic;
	
	friend class Alignement;
	friend class AlignementGet;
	friend class AlignementWrite;
	friend class pTest;
	friend class Path;
	friend class PathWalker;
	
	friend class mThread<class Path>;
	friend class mThreadRunning<class Path>;
	friend class mThreadWaiting<class Path>;
	
	friend class mThread<class PathWalker>;
	friend class mThreadRunning<class PathWalker>;
	friend class mThreadWaiting<class PathWalker>;
	
	friend class mThread<class Alignement>;
	friend class mThreadRunning<class Alignement>;
	friend class mThreadWaiting<class Alignement>;
	
	friend class mThread<class AlignementGet>;
	friend class mThreadRunning<class AlignementGet>;
	friend class mThreadWaiting<class AlignementGet>;
	
	friend class mThread<class AlignementWrite>;
	friend class mThreadRunning<class AlignementWrite>;
	friend class mThreadWaiting<class AlignementWrite>;
	
	friend class mThread<class pTest>;
	friend class mThreadRunning<class pTest>;
	friend class mThreadWaiting<class pTest>;
};

#endif

