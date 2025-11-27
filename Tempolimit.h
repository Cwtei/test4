/*
 * Tempolimit.h
 *
 *  Created on: Nov 9, 2025
 *      Author: cw
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_

#include <limits>

enum class Tempolimit
{
	Innerorts = 50, //speed limit of 50km/h
	Landstrasse = 100, //speed limit of 100km/h
	Autobahn = std::numeric_limits<int>::max() //no speed limit
};

double getTempolimit(Tempolimit tempolimit);

#endif /* TEMPOLIMIT_H_ */
