/*
 * Simulationsobjekt.h
 *
 *  Created on: Nov 9, 2025
 *      Author: cw
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <string>

class Simulationsobjekt {
public:
	Simulationsobjekt();
	Simulationsobjekt(std::string sName);
	virtual ~Simulationsobjekt();

	virtual void vSimulieren() = 0; //Update the movement of vehicles
	virtual void vAusgeben(std::ostream& out) const; //Print out data of vehicles
	bool operator == (const Simulationsobjekt& simulationsobjekt) const;

	std::string getName() const;
	virtual void vEinlesen(std::istream& in);

protected:
	double p_dZeit;

private:
	std::string p_sName;
	const int p_iID;
	static inline int p_iMaxID = 0;

	Simulationsobjekt(const Simulationsobjekt& other) = delete;
	Simulationsobjekt& operator=(const Simulationsobjekt& other) = delete;
};

std::ostream& operator << (std::ostream& out, const Simulationsobjekt& simulationsobjekt);
std::istream& operator >> (std::istream& in,  Simulationsobjekt& simulationsobjekt);

#endif /* SIMULATIONSOBJEKT_H_ */
