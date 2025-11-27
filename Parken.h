/*
 * Parken.h
 *
 *  Created on: Nov 10, 2025
 *      Author: cw
 */

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Parken: public Verhalten {
public:
	Parken(Weg& weg, double dStart);
	virtual ~Parken();

	// Throw exceptions if the car is moving (losfahren)
	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

	bool istFahrend() const override;

private:
	double p_dStart; //starting time of parking
};

extern double dGlobaleZeit;

#endif /* PARKEN_H_ */
