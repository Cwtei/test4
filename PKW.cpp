/*
 * PKW.cpp
 *
 *  Created on: Nov 4, 2025
 *      Author: cw
 */

#include "PKW.h"
#include "Weg.h"
#include "Verhalten.h"
#include "SimuClient.h"
#include <iomanip>
#include <iostream>


PKW::PKW(std::string sName, double dMaxGeschw, double dVerbrauch, double dTankvolumen):
		Fahrzeug(sName, dMaxGeschw),
		p_dVerbrauch(dVerbrauch),
		p_dTankvolumen (dTankvolumen),
		p_dTankinhalt (0.5 * dTankvolumen)
{}

double PKW::dTanken(double dMenge)
{
	double getankteMenge;
	if (dMenge == std::numeric_limits<double>::infinity() || dMenge + p_dTankinhalt >= p_dTankvolumen)
	{
		getankteMenge = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
	}
	else
	{
		getankteMenge = dMenge;
		p_dTankinhalt += dMenge;
	}
	return getankteMenge;
}

void PKW::vSimulieren()
{
	// dont move if the tank is empty
	if (p_dTankinhalt <= 0)
	{
		p_dZeit = dGlobaleZeit;
		return;
	}

	if (p_dZeit == dGlobaleZeit)
	{
		return;
	}

	// move the vehicle
	Fahrzeug::vSimulieren();

	//calculate the fuel consumption
	p_dTankinhalt = std::max(0.0, p_dTankinhalt - p_dGefahreneStrecke  * p_dVerbrauch/100.0);
}

void PKW::vAusgeben(std::ostream& out) const
{
	double gesamtverbrauch = p_dGesamtStrecke/100.0 * p_dVerbrauch;
	Fahrzeug::vAusgeben(out);
	out << std::resetiosflags(std::ios::left)
			<< std::setiosflags(std::ios::right)
			<< std::fixed
			<< std::setprecision(2)
			<< std::setw(17) << gesamtverbrauch << "   "
			<< std::setw(12) << p_dTankinhalt;
}

PKW::~PKW()
{}

// Taking the speed limit into account
double PKW::dGeschwindigkeit() const
{
	// Get speed limit of the current road from behavior
	double dWegLimit = p_pVerhalten->getWeg().getTempoLimitWeg();

	// Return lower of MaxSpeed or SpeedLimit
	if (p_dMaxGeschwindigkeit <= dWegLimit)
	{
		return p_dMaxGeschwindigkeit;
	}
	return dWegLimit;
}

// draw the vehicle
void PKW::vZeichnen(const Weg& weg) const
{
	bZeichnePKW(getName(), weg.getName(), p_dAbschnittStrecke/weg.getLaenge(),dGeschwindigkeit(),p_dTankinhalt);
}


bool PKW::istBehindernd() const
{
	return (p_pVerhalten->istFahrend() && p_dTankinhalt > 1e-9);
}

void PKW::vEinlesen(std::istream& in)
{
	Fahrzeug::vEinlesen(in);
	in >> p_dVerbrauch >> p_dTankvolumen;
}




