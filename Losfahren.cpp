/*
 * Losfahren.cpp
 *
 *  Created on: Nov 12, 2025
 *      Author: cw
 */

#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"

#include <iostream>

Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg): Fahrausnahme(fahrzeug, weg) {
	// TODO Auto-generated constructor stub

}

Losfahren::~Losfahren() {
	// TODO Auto-generated destructor stub
}

void Losfahren::vBearbeiten()
{
	std::cout << "Losfahren: " << p_rFahrzeug.getName()
                  << " (" << p_rWeg.getName() << ") " << std::endl;
	p_rWeg.vAnnahme(p_rWeg.pAbgabe(p_rFahrzeug));
}
