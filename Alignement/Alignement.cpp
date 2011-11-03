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

Alignement::Alignement(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, vector<double>* identity, string* muscle_path, int thread_id, string* tmp_rep)
{
	Alignement_fasta_a = fasta_a;
	Alignement_fasta_b = fasta_b;
	Alignement_hit_a = hit_a;
	Alignement_hit_b = hit_b;
	
	Alignement_path = muscle_path;
	Alignement_tmp_rep = tmp_rep;
	
	Alignement_id = thread_id;
	Alignement_identity = identity;
}

void Alignement::run()
{
	try
	{
		FastaThread seqa(Alignement_fasta_a, Alignement_hit_a);
		FastaThread seqb(Alignement_fasta_b, Alignement_hit_b);
		future<string*> first_seq = async(launch::async, seqa);
		future<string*> second_seq = async(launch::async, seqb);
		
		Alignement_first_seq = first_seq.get();
		Alignement_second_seq = second_seq.get();
		
		Alignement_identity->at(Alignement_hit_b->id()) = compute_identity();
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void Alignement::run()" << endl;
		exit(-1);
	}
}

void Alignement::operator()()
{
	Alignement::run();
}

void Alignement::operator()(Fasta* fasta_a, Hit* hit_a, Fasta* fasta_b, Hit* hit_b, vector<double>* identity, string* muscle_path, int thread_id, string* tmp_rep)
{
	Alignement_fasta_a = fasta_a;
	Alignement_fasta_b = fasta_b;
	Alignement_hit_a = hit_a;
	Alignement_hit_b = hit_b;
	
	Alignement_path = muscle_path;
	Alignement_tmp_rep = tmp_rep;
	
	Alignement_id = thread_id;
	Alignement_identity = identity;
	
	Alignement::run();
}

double Alignement::compute_identity()
{
	if(Alignement_first_seq->length() != Alignement_second_seq->length())
	{
		Alignement::align();
	}
	
	int size = Alignement_first_seq->length();
	int diff = 0;
	int gap = 0;
	double result = 0.0;
	
	try
	{
		for(int i = 0 ; i < size ; i++)
		{
			if(Alignement_first_seq->at(i) == 'N' || Alignement_second_seq->at(i) == 'N' || Alignement_first_seq->at(i) == '-' || Alignement_second_seq->at(i) == '-'){
				gap++;
			}else{
				if(Alignement_first_seq->at(i) != Alignement_second_seq->at(i)){
					diff++;
				}
			}
		}
		if(size-gap != 0)
		{
			result = ((double)(size-diff-gap)/(double)(size-gap))*100.0;
		}
		else
		{
			throw logic_error("Can not make a null division in double Alignement::identity()");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in double Alignement::identity()" << endl;
	}
	delete Alignement_first_seq;
	delete Alignement_second_seq;
	
	return result;
}

void Alignement::align_pipe()
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
		outputf.close();
		exit(-1);
	}
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
