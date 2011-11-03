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

#include "HitModel.hpp"

HitModel::HitModel()
{
	init(0, "", 0, 0);
}

HitModel::HitModel(string const & name, int start, int stop)
{
	init(0, name, start, stop);
}

HitModel::HitModel(int id, string const & name, int start, int stop)
{
	init(id, name, start, stop);
}

void HitModel::init(int id, string const & name, int start, int stop)
{
	try
	{
		if( start >= 0 && stop >= 0)
		{
			int tmp;
			if(start > stop)
			{
				tmp = start;
				start = stop;
				stop = tmp;
				Hit_sens = false;
			}
			else
			{
				Hit_sens = true;
			}
			Hit_id = id;
			Hit_name = name;
			Hit_start = start;
			Hit_stop = stop;
		}
		else
		{
			throw logic_error("Negatives positions");
		}
	}
	catch(exception const& e)
	{
		cerr << "ERROR : " << e.what() << " in void HitModel::init(int id, string const & name, int start, int stop)" << endl;
		init(0, "", 0, 0);
	}
}

HitModel::HitModel(HitModel const& Hitbis)
{
	Hit_id = Hitbis.id();
	Hit_sens = Hitbis.sens();
	Hit_name = Hitbis.name();
	Hit_start = Hitbis.start();
	Hit_stop = Hitbis.stop();
}

HitModel& HitModel::operator=(HitModel const& Hitbis)
{
	if(this != &Hitbis)
	{
		Hit_id = Hitbis.id();
		Hit_sens = Hitbis.sens();
		Hit_name = Hitbis.name();
		Hit_start = Hitbis.start();
		Hit_stop = Hitbis.stop();
	}
	return *this;
}

int HitModel::id() const
{
	return Hit_id;
}

bool HitModel::sens() const
{
	return Hit_sens;
}

int HitModel::start() const
{
	return Hit_start;
}

int HitModel::stop() const
{
	return Hit_stop;
}

string HitModel::name() const
{
	return Hit_name;
}

