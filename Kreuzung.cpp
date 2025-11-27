/*
 * Kreuzung.cpp
 *
 *  Created on: Nov 25, 2025
 *      Author: cw
 */

#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Tempolimit.h"

#include <memory>
#include <vector>
#include <list>
#include<random>

Kreuzung::Kreuzung(std::string sName, double dTankstelle):
Simulationsobjekt(sName),
p_dTankstelle(dTankstelle)
{
}

Kreuzung::~Kreuzung() {
	// TODO Auto-generated destructor stub
}

void Kreuzung::vTanken(Fahrzeug& fahrzeug)
{
	if (p_dTankstelle > 0.0)
	{
		p_dTankstelle -= fahrzeug.dTanken();
	}

}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStart)
{
	vTanken(*fahrzeug); //refuelling the vehicle

	if (!p_pWege.empty()) //check if p_pWege is empty or not to prevent error
	{
		p_pWege.front()->vAnnahme(std::move(fahrzeug), dStart);
	}
}

void Kreuzung::vSimulieren()
{
	for (auto it = p_pWege.begin(); it != p_pWege.end(); it++)
	{
		(*it)->vSimulieren();
	}

}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& weg)
{
	std::vector <std::shared_ptr<Weg>> moeglicheWege;

	for (auto it = p_pWege.begin(); it != p_pWege.end(); it++)
	{
		if ((*it)!= weg.getRueckweg())
		{
			moeglicheWege.push_back(*it);
		}
	}

	size_t anzahlMoeglicheWege = moeglicheWege.size();

	if (moeglicheWege.empty())
	{
		return weg.getRueckweg();
	}
	else
	{
		static std::mt19937 device(0);
		std::uniform_int_distribution<int>dist(0, (anzahlMoeglicheWege - 1));
		int zuf = dist(device);

		return moeglicheWege.at(zuf);
	}
}

void Kreuzung::addWeg(std::shared_ptr<Weg> pWeg)
{
	p_pWege.push_back(pWeg);
}

void Kreuzung::vVerbinde(
		std::string sNameHin,
		std::string sNameRueck,
		double dLaenge,
		Tempolimit eTempolimit,
		bool bUeberholverbot,
		std::shared_ptr<Kreuzung> pKreuzungStart,
		std::shared_ptr<Kreuzung> pKreuzungEnd )

{
	std::shared_ptr<Weg> weg1 = std::make_shared<Weg>(sNameHin, dLaenge, eTempolimit, bUeberholverbot, pKreuzungEnd);
	std::shared_ptr<Weg> weg2 = std::make_shared<Weg>(sNameRueck, dLaenge, eTempolimit, bUeberholverbot, pKreuzungStart);

	weg1->setRueckweg(weg2);
	weg2->setRueckweg(weg1);

	pKreuzungStart->addWeg(weg1);
	pKreuzungEnd->addWeg(weg2);
}

double Kreuzung::getTankstelle() const
{
	return p_dTankstelle;
}

void Kreuzung::vEinlesen(std::istream& in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dTankstelle;
}
