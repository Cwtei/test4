/*
 * Parken.cpp
 *
 *  Created on: Nov 10, 2025
 *      Author: cw
 */

#include "Parken.h"
#include "Weg.h"

#include "Losfahren.h"

#include<iostream>


Parken::Parken(Weg& weg, double dStart) : Verhalten(weg),p_dStart(dStart)
{}

Parken::~Parken() {
	// TODO Auto-generated destructor stub
}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	const double epsilon = 1e-9;

	// check if global tme has reached the start time
	if (dGlobaleZeit >= p_dStart-epsilon)
	{
		// Throw exception to switch behavior to "Driving"
		throw Losfahren(aFzg, p_rWeg);
	}

	return 0.0;
}

bool Parken::istFahrend() const
{
	return false;
}

