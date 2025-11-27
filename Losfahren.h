/*
 * Losfahren.h
 *
 *  Created on: Nov 12, 2025
 *      Author: cw
 */

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"

class Losfahren: public Fahrausnahme {
public:
	Losfahren(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Losfahren();

	void vBearbeiten() override;
};

#endif /* LOSFAHREN_H_ */
