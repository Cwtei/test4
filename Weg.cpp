/*
 * Weg.cpp
 *
 *  Created on: Nov 9, 2025
 *      Author: cw
 */

#include "Weg.h"
#include "Fahrzeug.h"
#include "Tempolimit.h"
#include "Fahrausnahme.h"

#include <iomanip>
#include <iostream>

Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit, bool bUeberholverbot, std::shared_ptr<Kreuzung> pZiel):
		Simulationsobjekt(sName),
		p_dLaenge(dLaenge),
		p_eTempolimit(eTempolimit),
		p_bUeberholverbot(bUeberholverbot),
		p_dSchranke (dLaenge),
		p_pRueckweg(),
		p_pZielKreuzung (pZiel)
{}

Weg::~Weg() {}


void Weg::vSimulieren()
{
	// Apply any pending changes to the list before simulation starts
	p_pFahrzeuge.vAktualisieren();

	p_dSchranke = p_dLaenge;

	for (auto& pFahrzeug : p_pFahrzeuge)
	{
		// exceptions reduce complexity
		// data wont need to be transferred multiple times across different classes
		// from parken or fahren to fahrzeug before reaching weg
		// reaching the end and losfahren are both exceptional case for dStrecke since its a function to return the distance the vehicle is gonna move

		try
		{
			pFahrzeug->vSimulieren();
			std::cout<< *pFahrzeug << std::endl;
			pFahrzeug->vZeichnen(*this); // Draw the vehicle

			// logic to update Schranke
			if (pFahrzeug->istBehindernd())
			{
				p_dSchranke = pFahrzeug->getAbschnittStrecke();
			}

		}
		catch (Fahrausnahme& e)
		{
			// Handle Streckenende and Losfahren scenario
			e.vBearbeiten();
		}
	}

	// Apply all changes
	p_pFahrzeuge.vAktualisieren();
}


void Weg::vAusgeben(std::ostream& out) const
{
	Simulationsobjekt::vAusgeben(out);
	out << " : " << std::resetiosflags(std::ios::left)
				<< std::setiosflags(std::ios::right)
				<< std::fixed
				<< std::setprecision(2)
				<< std::setw(8) << p_dLaenge << "   ("
				<< std::resetiosflags(std::ios::right)
				<< std::setiosflags(std::ios::left);

	auto it = p_pFahrzeuge.begin();
	while (it != p_pFahrzeuge.end())
	{
		out << (*it)->getName();

		if (++it != p_pFahrzeuge.end())
		{
			out << " ";
		}
	}

	out << ")";
}

void Weg::vKopf()
{
	std::cout << std::resetiosflags(std::ios::right)
			<< std::setiosflags(std::ios::left) //aligned to the left
			<<std::setw(3) << "ID" << " | "
			<< std::setw(5) << "Name" << " | "
			<< std::setw(8) << "Laenge" << " | "
			<< std::setw(20) << "Fahrzeuge" << " | "
			<< std::endl;
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug)
{
	fahrzeug->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(fahrzeug));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStart)
{
	fahrzeug->vNeueStrecke(*this, dStart);
	p_pFahrzeuge.push_front(std::move(fahrzeug));

}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug)
{
	// set it to return nullptr as the default
	std::unique_ptr<Fahrzeug> pRueckgabe = nullptr;

	auto it = p_pFahrzeuge.begin();
	while (it != p_pFahrzeuge.end())
	{
		if (*it && *(*it) == fahrzeug) // the first part *it is to check if its a nullptr or not
		{
			pRueckgabe = std::move(*it);
			p_pFahrzeuge.erase(it);
			return pRueckgabe;
		}
		it++;
	}
	return pRueckgabe;
}

void Weg::setRueckweg(std::shared_ptr <Weg> pRueckweg)
{
	p_pRueckweg = pRueckweg;
}

double Weg::getLaenge() const
{
	return p_dLaenge;
}

double Weg::getTempoLimitWeg() const
{
	return(getTempolimit(p_eTempolimit));
}

bool Weg::getUeberholverbot() const
{
	return p_bUeberholverbot;
}

double Weg::getSchranke() const
{
	return p_dSchranke;
}
