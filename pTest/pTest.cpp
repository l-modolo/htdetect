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

pTest::pTest(double chromosome_identity, pair<long int, long int> identity, unsigned int target_size, double* pvalue)
{
	pTest_chromosome_identity = chromosome_identity;
	pTest_identity = identity;
	pTest_target_size = target_size;
	pTest_pvalue = pvalue;
	pTest_statistic = nullptr;
}

pTest::pTest(double chromosome_identity, pair<long int, long int> identity, unsigned int target_size, double* pvalue, double* statistic)
{
	pTest_chromosome_identity = chromosome_identity;
	pTest_identity = identity;
	pTest_target_size = target_size;
	pTest_pvalue = pvalue;
	pTest_statistic = statistic;
}

pTest& pTest::operator=(pTest const& ptestbis)
{
	pTest_chromosome_identity = ptestbis.pTest_chromosome_identity;
	pTest_identity = ptestbis.pTest_identity;
	pTest_target_size = ptestbis.pTest_target_size;
	pTest_pvalue = ptestbis.pTest_pvalue;
	pTest_statistic = ptestbis.pTest_statistic;
}

void pTest::run()
{
	try
	{
		if(*pTest_pvalue == -1 && pTest_identity.first != -1)
		{
			double x = pTest_identity.first;
			double T = pTest_target_size - pTest_identity.second;
			double r = 1.0-(pTest_chromosome_identity/100.0); // we work on the differencies
			
			if(T < 0)
			{
				*pTest_pvalue = 1;
			}
			else
			{
				boost::math::poisson_distribution<> poisson(r*T);
//				boost::math::negative_binomial_distribution<> NB(T-x, r);
				*pTest_pvalue = boost::math::cdf(poisson, x);
//				*pTest_pvalue = boost::math::cdf(NB, x);
				if(pTest_statistic != nullptr)
				{
					*pTest_statistic = boost::math::pdf(poisson, x);
//					*pTest_statistic = boost::math::pdf(NB, T-x);
				}
			}
		}
		if(*pTest_pvalue == -1)
		{
			*pTest_pvalue == 1;
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in : void pTest::run()" << endl;
		*pTest_pvalue = 1;
	}
}

void pTest::operator()()
{
	pTest::run();
}

