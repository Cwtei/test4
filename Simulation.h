/*
 * Simulation.h
 *
 *  Created on: Nov 26, 2025
 *      Author: cw
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <memory>
#include <map>

class Kreuzung;

class Simulation {
public:
	Simulation();
	virtual ~Simulation();

	// Reads the network. bMitGrafik triggers reading coordinates (Task 9a)
	    void vEinlesen(std::istream& in, bool bMitGrafik = false);

	    // Runs the simulation
	    void vSimulieren(double dDauer, double dZeitschritt);

	private:
	    // Container for the network (Name -> Object)
	    std::map<std::string, std::shared_ptr<Kreuzung>> p_mKreuzungen;
};

#endif /* SIMULATION_H_ */
