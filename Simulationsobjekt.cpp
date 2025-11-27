/*
 * Simulationsobjekt.cpp
 *
 *  Created on: Nov 9, 2025
 *      Author: cw
 */

#include "Simulationsobjekt.h"
#include <string>
#include <iomanip>
#include <iostream>

Simulationsobjekt::Simulationsobjekt() : p_dZeit(0.0), p_sName(""), p_iID(++p_iMaxID)
{}

Simulationsobjekt::Simulationsobjekt(std::string sName) : p_dZeit(0.0), p_sName(sName), p_iID(++p_iMaxID)
{}

Simulationsobjekt::~Simulationsobjekt()
{
	std::cout  << "Destruktor: Simulationsobjekt " << p_iID << "(" << p_sName << ") wurde geloescht." << std::endl;
}

void Simulationsobjekt::vAusgeben(std::ostream& out) const
{
	out << std::resetiosflags(std::ios::right)
			<< std::setiosflags(std::ios::left)
			<< std::setw(3) << p_iID << "   "
			<< std::setw(9) << p_sName ;
}

void Simulationsobjekt::vEinlesen(std::istream& in)
{
	if (p_sName != "")
	{
		throw std::runtime_error("Fehler: Objekt existiert!");
	}

	in >> p_sName;
}

std::ostream& operator << (std::ostream& out, const Simulationsobjekt& simulationsobjekt)
{
	simulationsobjekt.vAusgeben(out);
	return out;
}

std::istream& operator >> (std::istream& in, Simulationsobjekt& simulationsobjekt)
{
	simulationsobjekt.vEinlesen(in);
	return in;
}

bool Simulationsobjekt::operator == (const Simulationsobjekt& simulationsobjekt) const
{
	return (this->p_iID == simulationsobjekt.p_iID);
}

std::string Simulationsobjekt::getName() const
{
	return p_sName;
}


