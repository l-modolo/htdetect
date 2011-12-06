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

#ifndef DEF_pTest
#define DEF_pTest

#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <boost/math/distributions/poisson.hpp>
#include <boost/math/special_functions/round.hpp>
#include "../Hit/Hit.hpp"

using namespace std;

class pTest {
	public:
	pTest(double chromosome_identity, double identity, unsigned int target_size, double* pvalue);
	pTest(double chromosome_identity, double identity, unsigned int target_size, double* pvalue, double* statistic);
	pTest& operator=(pTest const& ptestbis);
	
	void run();
	void operator()();
	
	protected:
	double pTest_chromosome_identity;
	double pTest_identity;
	unsigned int pTest_target_size;
	unsigned int pTest_hit_target_id;
	double* pTest_pvalue;
	double* pTest_statistic;
};


#endif
