/*
 * Fahrrad.cpp
 *
 *  Created on: Nov 4, 2025
 *      Author: cw
 */

#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"
#include "Verhalten.h"
#include <algorithm>
#include <cmath>

Fahrrad::Fahrrad(std::string sName, double dMaxGeschw): Fahrzeug(sName, dMaxGeschw)
{}

Fahrrad::~Fahrrad()
{}


double Fahrrad::dGeschwindigkeit() const
{
	// speed reduction calculation logic (10% speed reduction for every 20km driven
	int iMultipleOf20 = static_cast<int> (p_dGesamtStrecke / 20.0); // static cast to change float into integer
	double dGeschw = p_dMaxGeschwindigkeit * std::pow(0.9 , iMultipleOf20);

	//never go lower than 12km/h
	return std::max(dGeschw , 12.0);
}

void Fahrrad::vZeichnen(const Weg& weg) const
{
	bZeichneFahrrad(getName(), weg.getName(), p_dAbschnittStrecke/weg.getLaenge(),dGeschwindigkeit());
}

bool Fahrrad::istBehindernd() const
{
	return p_pVerhalten->istFahrend();
}

void Fahrrad::vEinlesen(std::istream& in)
{
	Fahrzeug::vEinlesen(in);
}
