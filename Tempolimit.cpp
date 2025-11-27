/*
 * Tempolimit.cpp
 *
 *  Created on: Nov 9, 2025
 *      Author: cw
 */

#include "Tempolimit.h"
#include <limits>

double getTempolimit(Tempolimit tempolimit)
{
	switch (tempolimit)
	{
	case Tempolimit::Innerorts:
		return 50.0;
	case Tempolimit::Landstrasse:
		return 100.0;
	case Tempolimit::Autobahn:
		return static_cast<double>(std::numeric_limits<int>::max());
	default:
		return static_cast<double>(std::numeric_limits<int>::max());
	}
}



