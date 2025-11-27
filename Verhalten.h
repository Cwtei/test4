/*
 * Verhalten.h
 *
 *  Created on: Nov 10, 2025
 *      Author: cw
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_


class Fahrausnahme;
class Fahrzeug;
class Weg;

class Verhalten {
public:
	Verhalten(Weg& weg);
	virtual ~Verhalten();
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;
	virtual Weg& getWeg() const;
	virtual bool istFahrend() const = 0;

protected:
	Weg& p_rWeg;
};

#endif /* VERHALTEN_H_ */
