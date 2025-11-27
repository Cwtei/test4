/*
 * Fahren.cpp
 *
 *  Created on: Nov 10, 2025
 *      Author: cw
 */

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

Fahren::Fahren(Weg& weg) : Verhalten(weg) {
	// TODO Auto-generated constructor stub

}

Fahren::~Fahren() {
	// TODO Auto-generated destructor stub
}


double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	// Calculate distance remaining on the road
	double dRest = p_rWeg.getLaenge() - aFzg.getAbschnittStrecke();

	// float comparison
	const double epsilon = 1e-9;
	if (dRest < epsilon)
	{
		// throw exception to signal the road that this vehicle is at the end
		throw Streckenende(aFzg, p_rWeg);
		return 0.0;
	}

	// Possible distance by ignoring the actual distance remaining
	double dMoeglich = aFzg.dGeschwindigkeit() * dZeitIntervall;

	if (p_rWeg.getUeberholverbot())
	{
		double dFahrzeugAmVorne = p_rWeg.getSchranke() - aFzg.getAbschnittStrecke();
		return(std::min({dMoeglich, dRest, dFahrzeugAmVorne}));
	}

	// Move by not exceeding the road length
	return(std::min(dMoeglich, dRest));
}

bool Fahren::istFahrend() const
{
	return true;
}
