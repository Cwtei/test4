/*
 * Weg.h
 *
 *  Created on: Nov 9, 2025
 *      Author: cw
 */

#ifndef WEG_H_
#define WEG_H_

#include <list>
#include <memory>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

class Kreuzung;
class Fahrausnahme;
class Fahrzeug;

class Weg: public Simulationsobjekt
{
public:
	Weg() = delete;
	Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn, bool bUeberholverbot = true, std::shared_ptr<Kreuzung> pZiel = nullptr);

	virtual ~Weg();

	// simulates all the vehicles on this road
	void vSimulieren() override;

	// print out the information of the street
	void vAusgeben(std::ostream& out) const override;

	// Prints the table header
	static void vKopf();

	// Assign a fahrzeug as fahrend on this weg
	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);

	// Assign a fahrzeug as parken on this weg
	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStart);

	// Removes a vehicle from the road (transfer ownership)
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);

	void setRueckweg(std::shared_ptr <Weg> pRueckweg);

	double getLaenge() const;
	double getTempoLimitWeg() const;
	bool getUeberholverbot() const;
	double getSchranke() const;
	std::shared_ptr<Weg> getRueckweg() {return p_pRueckweg.lock();}
	std::shared_ptr<Kreuzung> getZielKreuzung() const {return p_pZielKreuzung.lock();}

private:
	double p_dLaenge; //distance in km
	vertagt::VListe <std::unique_ptr<Fahrzeug>> p_pFahrzeuge; // list of vehicles on this 'weg'
	Tempolimit p_eTempolimit;
	bool p_bUeberholverbot; // when true that means there is a Ueberholverbot
	double p_dSchranke;

	// why is this not const, find out the answer after the function verbinden is completed
	// Since a const variable can only be initialized once (in the initializer list) and cannot be assigned to afterward,
	std::weak_ptr<Weg> p_pRueckweg;
	const std::weak_ptr<Kreuzung> p_pZielKreuzung;
};

#endif /* WEG_H_ */
