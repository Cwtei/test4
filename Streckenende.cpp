/*
 * Streckenende.cpp
 *
 *  Created on: Nov 12, 2025
 *      Author: cw
 */

#include "Simulationsobjekt.h"
#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"

#include <iostream>
#include<iomanip>

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg): Fahrausnahme(fahrzeug, weg) {
	// TODO Auto-generated constructor stub

}

Streckenende::~Streckenende() {
	// TODO Auto-generated destructor stub
}

void Streckenende::vBearbeiten()
{
	std::shared_ptr <Kreuzung> pKreuzung = p_rWeg.getZielKreuzung();
	std::shared_ptr <Weg> pNewWeg = pKreuzung->pZufaelligerWeg(p_rWeg);

	std::cout << std::endl;
	std::cout << "ZEIT      : " << std::fixed << std::setprecision(2) << dGlobaleZeit << std::endl;
	std::cout << "KREUZUNG  : " << pKreuzung->getName() << " [" << pKreuzung->getTankstelle() << " l]" << std::endl;
	std::cout << "WECHSEL   : " << p_rWeg.getName() << " -> " << pNewWeg->getName() << std::endl;
	// Output Fahrzeug data via its overloaded operator<<
	std::cout << "FAHRZEUG  : " << p_rFahrzeug << std::endl;
	std::cout << std::endl;

	pKreuzung->vTanken(p_rFahrzeug);
	pNewWeg->vAnnahme(p_rWeg.pAbgabe(p_rFahrzeug));

}
