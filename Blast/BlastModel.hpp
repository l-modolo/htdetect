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
#include "../HitList/HitList.hpp"
#include "../Fasta/Fasta.hpp"
#include "../ProgressBar/ProgressBar.hpp"

using namespace std;

class BlastModel
{
	public:
	BlastModel();
	BlastModel(string const & name, string const & file);
	BlastModel(string const & name, string const & file, string const & muscle_path);
	BlastModel(string const & name, string const & file, Fasta* fasta1);
	BlastModel(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2);
	BlastModel(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2, string const & muscle_path);
	BlastModel(BlastModel & Blastbis);
	~BlastModel();
	
	void sav();
	void restore(string const & file, Fasta* fasta_a, Fasta* fasta_b);
	void load(string const & name, string const & file, Fasta* fasta1, Fasta* fasta2);
	
	string name() const;
	string file() const;
	int size() const;
	
	Hit* hit_query(int i);
	Hit* hit_target(int i);
	Hit* hit_target(int i, int j);
	HitList* target(int i);
	
	int hit_target_size(int i);
	double identity(int i, int j);
	double pvalue(int i, int j);
	bool neighbor_prev(int i, int j);
	bool neighbor_next(int i, int j);
	
	void set_pvalue(int i, int j, double value);
	void set_neighbor_prev(int i, int j, bool value);
	void set_neighbor_next(int i, int j, bool value);
	
	protected:
	void read();
	
	Fasta* Blast_fasta_a;
	Fasta* Blast_fasta_b;
	string Blast_muscle_path;
	string Blast_file;
	string Blast_name;
	
	HitList Blast_query;
	vector<HitList*> Blast_target;
	
	vector<bool> Blast_neighbor_prev;
	vector<bool> Blast_neighbor_next;
	vector<double> Blast_identity;
	vector<double> Blast_pvalue;
	
	friend class Alignement;
};

#endif

