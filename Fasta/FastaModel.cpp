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


