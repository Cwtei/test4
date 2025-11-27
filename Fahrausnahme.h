/*
 * Fahrausnahme.h
 *
 *  Created on: Nov 12, 2025
 *      Author: cw
 */

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <exception>

class Fahrzeug;
class Weg;

class Fahrausnahme : public std::exception
{
public:
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Fahrausnahme();
	virtual void vBearbeiten() = 0;

protected:
	Fahrzeug& p_rFahrzeug;
	Weg& p_rWeg;
};

#endif /* FAHRAUSNAHME_H_ */
