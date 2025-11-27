/*
 * Verhalten.cpp
 *
 *  Created on: Nov 10, 2025
 *      Author: cw
 */

#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"

Verhalten::Verhalten(Weg& weg) : p_rWeg(weg) {}

Verhalten::~Verhalten() {
	// TODO Auto-generated destructor stub
}


Weg& Verhalten::getWeg() const
{
	return p_rWeg;
}
