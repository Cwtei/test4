/*
 * Fahrzeug.h
 *
 *  Created on: Nov 3, 2025
 *      Author: cw
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "Simulationsobjekt.h"

#include <string>
#include <limits>

class Verhalten;
class Weg;

class Fahrzeug: public Simulationsobjekt
{
public:
	Fahrzeug();
	Fahrzeug(std::string sName);
	Fahrzeug(std::string sName, double dMaxGeschw);
	virtual ~Fahrzeug();


	// Print out table header for Fahrzeug
	static void vKopf();


	void vSimulieren() override;
	void vAusgeben(std::ostream& out) const override;
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

	// return the speed of the fahrzeug
	virtual double dGeschwindigkeit() const;

	bool operator < (const Fahrzeug& fahrzeug) const;

	// Assign the Verhalten fahrend to the fahrzeug
	virtual void vNeueStrecke(Weg& weg);

	// Assign the Verhalten parken to the fahrzeug (dStart is the time the fahrzeug starts moving)
	virtual void vNeueStrecke(Weg& weg, double dStart);

	double getAbschnittStrecke() const;

	virtual void vZeichnen(const Weg& weg) const = 0;

	virtual bool istBehindernd() const = 0;

	void vEinlesen(std::istream& in) override;

	double getMaxGeschwindigkeit() const {return p_dMaxGeschwindigkeit;}

protected:
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit; // Total time travelled
	double p_dAbschnittStrecke;
	double p_dGefahreneStrecke; //self-added member

	// Behaviour (fahrend or parken)
	std::unique_ptr<Verhalten> p_pVerhalten;
};

extern double dGlobaleZeit;

#endif /* FAHRZEUG_H_ */
