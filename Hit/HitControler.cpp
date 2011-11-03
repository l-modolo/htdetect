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

#include "HitControler.hpp"

HitControler::HitControler() : HitModel::HitModel() {}
HitControler::HitControler(string const & name, int start, int stop) : HitModel::HitModel(name, start, stop) {}
HitControler::HitControler(int id, string const & name, int start, int stop) : HitModel::HitModel(id, name, start, stop) {}

int HitControler::size() const
{
	return Hit_stop - Hit_start;
}

bool HitControler::operator<(HitControler const& Hitbis) const
{
	return Hit_stop < Hitbis.start();
}

bool HitControler::operator>(HitControler const& Hitbis) const
{
	return Hit_start > Hitbis.stop();
}

bool HitControler::operator<=(HitControler const& Hitbis) const
{
	return Hit_stop <= Hitbis.start();
}

bool HitControler::operator>=(HitControler const& Hitbis) const
{
	return Hit_start >= Hitbis.stop();
}

bool HitControler::operator==(HitControler const& Hitbis) const
{
	if(Hit_start == Hitbis.start() && Hit_stop == Hitbis.stop())
	{
		return true;
	}
	return false;
}

bool HitControler::operator==(HitControler* const& Hitbis) const
{
	if(Hit_start == Hitbis->start() && Hit_stop == Hitbis->stop())
	{
		return true;
	}
	return false;
}

bool HitControler::operator!=(HitControler const& Hitbis) const
{
	if(Hit_start != Hitbis.start() || Hit_stop != Hitbis.stop())
	{
		return true;
	}
	return false;
}

bool HitControler::in(HitControler const& Hitbis) const
{
	if(Hitbis.stop() <= Hit_stop && Hit_start <= Hitbis.start())
	{
		return true;
	}
	return false;
}

bool HitControler::over(HitControler const& Hitbis) const
{
	if(this != &Hitbis)
	{
		if(Hitbis.start() <= Hit_start && Hit_start <= Hitbis.stop())
			return true;
		if(Hitbis.start() <= Hit_stop && Hit_stop <= Hitbis.stop())
			return true;
	
		if(Hit_start <= Hitbis.start() && Hitbis.start() <= Hit_stop)
			return true;
		if(Hit_start <= Hitbis.stop() && Hitbis.stop() <= Hit_stop)
			return true;
	}
	return false;
}

bool HitControler::over(int start, int stop) const
{
	if(start <= Hit_start && Hit_start <= stop)
		return true;
	if(start <= Hit_stop && Hit_stop <= stop)
		return true;
	if(Hit_start <= start && start <= Hit_stop)
		return true;
	if(Hit_start <= stop && stop <= Hit_stop)
		return true;
	
	return false;
}

