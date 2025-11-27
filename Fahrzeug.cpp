/*
 * Fahrzeug.cpp
 *
 *  Created on: Nov 3, 2025
 *      Author: cw
 */

#include "Fahrzeug.h"
#include "Verhalten.h"
#include <iostream>
#include <iomanip>
#include <cmath>

#include "Verhalten.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"

Fahrzeug::Fahrzeug():
Simulationsobjekt(),
p_dMaxGeschwindigkeit(0.0),
p_dGesamtStrecke(0.0),
p_dGesamtZeit(0.0),
p_dAbschnittStrecke(0.0),
p_dGefahreneStrecke (0.0),
p_pVerhalten(nullptr)

{}

Fahrzeug::Fahrzeug(std::string sName):
		Simulationsobjekt(sName),
		p_dMaxGeschwindigkeit(0.0),
		p_dGesamtStrecke(0.0),
		p_dGesamtZeit(0.0),
		p_dAbschnittStrecke(0.0),
		p_dGefahreneStrecke (0.0),
		p_pVerhalten(nullptr)

{}

Fahrzeug::Fahrzeug(std::string sName, double dMaxGeschw):
		Simulationsobjekt(sName),
		p_dMaxGeschwindigkeit ((dMaxGeschw >= 0) ? dMaxGeschw : 0.0), //0.0 is used for type consistency
		p_dGesamtStrecke(0.0),
		p_dGesamtZeit(0.0),
		p_dAbschnittStrecke(0.0),
		p_dGefahreneStrecke (0.0),
		p_pVerhalten(nullptr)
{}

void Fahrzeug::vSimulieren()
{
	// Ensure we dont simulate twice in the same time step
	if (p_dZeit == dGlobaleZeit)
	{
		return;
	}

	double dT = dGlobaleZeit - p_dZeit;
	p_dGesamtZeit += dT;
	p_dZeit = dGlobaleZeit;

	// Ask the Behaviour object how far can we drive
	// Throw exceptions if we reach the end (streckenende) or start driving (losfahren)
	// this is the pointer to the current Fahrzeug, *this will dereference it
	p_dGefahreneStrecke = p_pVerhalten->dStrecke(*this, dT);

	// Equal to zero when there is a 'weg' change
	p_dAbschnittStrecke += p_dGefahreneStrecke;
	p_dGesamtStrecke += p_dGefahreneStrecke;
}

void Fahrzeug::vAusgeben(std::ostream& out) const
{
	Simulationsobjekt::vAusgeben(out);
	out << "   " << std::resetiosflags(std::ios::left)
		<< std::setiosflags(std::ios::right)
		<< std::fixed
		<< std::setprecision(2)
		<< std::setw(20) << p_dMaxGeschwindigkeit << "   "
		<< std::setw(17) << dGeschwindigkeit() << "   "
		<< std::setw(15) << p_dGesamtStrecke << "   ";
}


void Fahrzeug::vKopf()
{
	std::cout << std::resetiosflags(std::ios::right)
			<< std::setiosflags(std::ios::left) //aligned to the left
			<<std::setw(3) << "ID" << " | "
			<< std::setw(9) << "Name" << " | "
			<< std::resetiosflags(std::ios::left)
			<< std::setiosflags(std::ios::right)
			<< std::setw(20) << "MaxGeschwindigkeit" << " | "
			<< std::setw(17) << "Geschwindigkeit" << " | "
			<< std::setw(15) << "Gesamtstrecke" << " | "
			<< std::setw(17) << "Gesamtverbrauch" << " | "
			<< std::setw(12) << "Tankinhalt"
			<< std::endl;
}

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

Fahrzeug::~Fahrzeug()
{}


bool Fahrzeug::operator < (const Fahrzeug& fahrzeug) const
{
	return (this->p_dGesamtStrecke < fahrzeug.p_dGesamtStrecke);
}


double Fahrzeug::getAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

// Initialises driving behaviour
void Fahrzeug::vNeueStrecke(Weg& weg)
{
	p_pVerhalten = std::make_unique <Fahren> (weg);
	p_dAbschnittStrecke = 0.0;

}

// Initialises parking behaviour
void Fahrzeug::vNeueStrecke(Weg& weg, double dStart)
{
	p_pVerhalten = std::make_unique <Parken> (weg,dStart);
	p_dAbschnittStrecke = 0.0;
	p_dZeit = dStart;

}

void Fahrzeug::vEinlesen(std::istream& in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dMaxGeschwindigkeit;
}
