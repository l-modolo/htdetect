#ifndef DEF_Sequence
#define DEF_Sequence

#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>

using namespace std;

class Sequence {
	public:
	Sequence(string const & name, long long int start, long long int stop, int line);
	
	bool operator==(Sequence const& Sequencebis) const;
	
	long long int start();
	long long int stop();
	int lines();
	
	long long int size() const;
	long long int pos(int from) const;
	bool in(long long int pos) const;
	
	protected:
	// attributes
	string Sequence_name;
	long long int Sequence_start;
	long long int Sequence_stop;
	int Sequence_line_size;
	
	private:
	void display(ostream &stream) const;
	
	friend std::ostream& operator<< (std::ostream& flux, Sequence const&s);
};


#endif
