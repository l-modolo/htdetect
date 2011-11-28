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

#include "pTest.hpp"

pTest::pTest(double chromosome_identity, double identity, unsigned int target_size, unsigned int id, vector<double>* pvalue)
{
	pTest_chromosome_identity = chromosome_identity;
	pTest_identity = identity;
	pTest_target_size = target_size;
	pTest_hit_target_id = id;
	pTest_pvalue = pvalue;
}

pTest& pTest::operator=(pTest const& ptestbis)
{
	pTest_chromosome_identity = ptestbis.pTest_chromosome_identity;
	pTest_identity = ptestbis.pTest_identity;
	pTest_target_size = ptestbis.pTest_target_size;
	pTest_hit_target_id = ptestbis.pTest_hit_target_id;
	pTest_pvalue = ptestbis.pTest_pvalue;
}

void pTest::run()
{
	try
	{
		if(pTest_pvalue->at(pTest_hit_target_id) == -1 && pTest_identity != -1.0)
		{
			double x;
			double T = pTest_target_size;
			double r = 1.0-(pTest_chromosome_identity/100.0);;
		
			if(pTest_identity > pTest_chromosome_identity)
			{
				x = round((1.0-(pTest_identity/100.0))*T);
				
				boost::math::poisson_distribution<> poisson(r*T);
				pTest_pvalue->at(pTest_hit_target_id) = boost::math::cdf(poisson, x);
			}
			else
			{
				pTest_pvalue->at(pTest_hit_target_id) = 1;
			}
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void pTest::run()" << endl;
		exit(-1);
	}
}

void pTest::operator()()
{
	pTest::run();
}

