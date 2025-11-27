/*
 * main.cpp
 *
 *  Created on: Nov 3, 2025
 *      Author: cw
 */

#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "Tempolimit.h"
#include "SimuClient.h"
#include "vertagt_liste.h"
#include "Kreuzung.h"
#include "Simulation.h"

#include <memory> //for smart pointer
#include <iostream>
#include <vector> //for container vector
#include <utility> //for move()
#include <random> // to generate random numbers
#include <fstream> //file reading
#include <exception>


void vAufgabe_9a();

double dGlobaleZeit = 0.0; //Global variable to be accessible from other classes

int main()
{
	vAufgabe_9a();
}

/*
void vAufgabe_1()
{
	std::cout << "----------------- Raw pointer test -----------------" << std::endl;
	//construct stack object (object created in stack memory will be deleted automatically)
	Fahrzeug stack("stack");

	//construct heap object
	Fahrzeug* heap = new Fahrzeug("heap");

	//clearing heap memory (pointer saved in the heap must be deleted manually)
	delete heap;

	std::cout << "----------------- Smart pointer test -----------------" << std::endl;

	//unique pointer
	//data type: std::unique_ptr<T>
	//declaration: std::make_unique<T>(C)
	//T is the class of the object to be constructed
	//C is the input for the constructor (works with or without input due to the default constructor
	std::unique_ptr <Fahrzeug> unique1_ptr = std::make_unique <Fahrzeug> ("Unique1");
	std::unique_ptr <Fahrzeug> unique2_ptr = std::make_unique <Fahrzeug> ("Unique2");

	std::vector<std::unique_ptr<Fahrzeug>> unique_vector;

	//std::move is required to transfer the pointer
	//unique_ptr are now nullptr and the object is owned by the 'unique_vector'
	unique_vector.push_back(std::move(unique1_ptr));
	unique_vector.push_back(std::move(unique2_ptr));

	//shared pointer
	//data type: std::shared_ptr<T>
	//declaration: std::make_shared<T>(C)
	//T is the class of the object to be constructed
	//C is the input for the constructor (works with or without input due to the default constructor
	std::shared_ptr <Fahrzeug> shared1_ptr = std::make_shared <Fahrzeug> ("Shared1");
	std::shared_ptr <Fahrzeug> shared2_ptr = std::make_shared <Fahrzeug> ("Shared2");

	std::cout << "Count (shared1_ptr): " << shared1_ptr.use_count() << std::endl; //output: 1

	shared2_ptr = shared1_ptr; //count increases as the object is pointed more, shared2_ptr is deleted

	std::cout << "Count (shared1_ptr): " << shared1_ptr.use_count() << std::endl; //output: 2


	std::vector<std::shared_ptr<Fahrzeug>> shared_vector;

	//std::move is not required
	//both shared_vector and shared_ptr own the object and the count increases
	shared_vector.push_back(shared1_ptr);
	shared_vector.push_back(shared2_ptr);
}
*/

/*
void vAufgabe_1a()
{
	std::string name;
	double maxSpeed;
	std::vector<std::unique_ptr<Fahrzeug>> vehicle_vector;

	for (int i=1; i<=3 ; i++)
	{
		std::cout << "Enter the name of the vehicle: " ;
		std:: cin >> name;
		std::cout << "Enter the max speed of the vehicle: " ;
		std:: cin >> maxSpeed;
		std::unique_ptr <Fahrzeug> vehicle_ptr = std::make_unique <Fahrzeug> (name, maxSpeed);
		vehicle_vector.push_back(std::move(vehicle_ptr));
	}

	Fahrzeug::vKopf();
	std::cout << "\n------------------------------------------------------------------------------\n" << std::endl;

	for (int j=1; j<=3; j++)
	{
		dGlobaleZeit += 0.5;

		auto it = vehicle_vector.begin();
		while (it != vehicle_vector.end())
		{
			(*it)->vSimulieren();
			std::cout << *(*it);
			std::cout << std::endl;
			it++;
		}
	}
}
*/

void vAufgabe_2()
{
	std::string sName;
	double dMaxGeschw;
	std::vector<std::unique_ptr<Fahrzeug>> vehicle_vector;


	std::cout << "How many PKWs are there: ";
	int iNumberOfPKW;
	std::cin >> iNumberOfPKW;

	double dVerbrauch, dTankvolumen;
	for (int i=1; i<=iNumberOfPKW ; i++)
	{
		std::cout << "PKW " << i << std::endl;
		std::cout << "Name: " ;
		std:: cin >> sName;
		std::cout << "Max speed: " ;
		std:: cin >> dMaxGeschw;
		std::cout << "Verbrauch: ";
		std::cin >> dVerbrauch;

		char choice;
		std::cout << "Use default tank volume (55.0)? (y/n)";
		std::cin >> choice;

		if (choice == 'n' || choice == 'N')
		{
			std::cout << "Custom tank volume: " ;
			std::cin >> dTankvolumen;
			std::unique_ptr <PKW> vehicle_ptr = std::make_unique <PKW> (sName, dMaxGeschw, dVerbrauch, dTankvolumen);
			vehicle_vector.push_back(std::move(vehicle_ptr));
		}
		else
		{
			std::unique_ptr <PKW> vehicle_ptr = std::make_unique <PKW> (sName, dMaxGeschw, dVerbrauch);
			vehicle_vector.push_back(std::move(vehicle_ptr));
		}
	}

	std::cout << "How many Fahrrads are there: " ;
	int iNumberOfFahrrad;
	std::cin >> iNumberOfFahrrad;

	for (int i=1; i<=iNumberOfFahrrad; i++)
	{
		std::cout << "Fahrrad " << i << std::endl;
		std::cout << "Name: " ;
		std:: cin >> sName;
		std::cout << "Max speed: " ;
		std:: cin >> dMaxGeschw;

		std::unique_ptr <Fahrrad> vehicle_ptr = std::make_unique <Fahrrad> (sName, dMaxGeschw);
		vehicle_vector.push_back(std::move(vehicle_ptr));
	}

	Fahrzeug::vKopf();
	std::cout << "-----------------------------------------------------------------------------------------\n" ;

	double dDauer = 10;
	double dZeitschritt = 0.5;

	for (dGlobaleZeit = 0; dGlobaleZeit <= dDauer; dGlobaleZeit += dZeitschritt)
	{

		std::cout << "Simulation time: " << dGlobaleZeit << std::endl;

		//simulate the movement
		auto it = vehicle_vector.begin();
		while (it != vehicle_vector.end())
		{
			(*it)->vSimulieren();
			it++;
		}

		//refueling
		const double epsilon = 1e-9;
		if (dGlobaleZeit > 3.0 - epsilon && dGlobaleZeit - dZeitschritt < 3.0 - epsilon)
		{
			std::cout << "Refueling" << std::endl;



			for (int i = 0; i < iNumberOfPKW; i++)
			{
				//vehicle_vectors is a sequence of smart pointers
				//vehicle_vector[i] accesses the i-th element, which is an object of type std::unique_ptr<Fahrzeug>
				//std::unique_ptr<Fahrzeug> is a wrapper around a raw memory address a Fahrzeug*
				//get() tells the smart pointer to hand out its inner raw address
				//dynamic casting return the valid pointer if successful, and nullptr if unsuccessful
				PKW* pPKW = dynamic_cast<PKW*> (vehicle_vector[i].get());

				if (pPKW) //anything except nullptr is considered true
				{
					pPKW->dTanken();
				}
			}
		}

		//print out the vector
		it = vehicle_vector.begin();
		while (it != vehicle_vector.end())
		{
			std::cout << *(*it);
			std::cout << std::endl;
			it++;
		}
	}
}

void vAufgabe_4()
{
    std::cout << "AUFGABENBLOCK 2 5.3" << std::endl;

    std::unique_ptr<Weg> pWeg1 = std::make_unique<Weg>("WegA", 40.0);
    std::unique_ptr<Weg> pWeg2 = std::make_unique<Weg>("WegB", 115.0, Tempolimit::Landstrasse);

    Weg::vKopf();
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << *pWeg1 << std::endl;
    std::cout << *pWeg2 << std::endl;
}

void vAufgabe_5()
{
	std::cout << "AUFGABENBLOCK 2 5.4" << std::endl;

	// Einen Weg erzeugen
    std::unique_ptr<Weg> pWeg = std::make_unique<Weg>("Weg1", 100.0); //Laenge 100km


    // 3 Fahrzeuge erzeugen
    auto pBMW = std::make_unique<PKW>("BMW", 120.0, 10.0, 55.0); // Name, MaxSpeed, Consumption, TankVolume
    auto pAudi = std::make_unique<PKW>("Audi", 100.0, 8.0, 50.0);
    auto pBMX = std::make_unique<Fahrrad>("BMX", 25.0); // Name, MaxSpeed

    // Fahrzeuge auf den Weg setzen
    pWeg->vAnnahme(std::move(pBMW)); //Als fahren angenommen (hinten der Liste)
    pWeg->vAnnahme(std::move(pAudi), 3.0); //Als parken angenommen mit Startzeit 3.0 (vorne der Liste)
    pWeg->vAnnahme(std::move(pBMX), 1.0); //Als parken angenommen mit Startzeit 1.0 (vorne der Liste)

    // Simulation durchführen
    double dZeitschritt = 0.25;
    double dMaxZeit = 5.0;

    std::cout << "\n--- Starte Simulation ---\n" << std::endl;

    Weg::vKopf();

    for (dGlobaleZeit = 0.0; dGlobaleZeit <= dMaxZeit; dGlobaleZeit += dZeitschritt)
    {
        std::cout << "\n>>> Globale Zeit: " << dGlobaleZeit << std::endl;

        pWeg->vSimulieren();

        std::cout << *pWeg << std::endl;
    }
}

void vAufgabe_6()
{
	// create two roads (smart pointers)
	std::unique_ptr<Weg> autobahn = std::make_unique <Weg> ("Inner", 500.0);
	std::unique_ptr<Weg> landstrasse = std::make_unique <Weg> ("Land", 500.0, Tempolimit::Landstrasse);


	// create vehicles (smart pointers)
	auto pBMW = std::make_unique<PKW>("BMW", 300.0, 10.0, 120.0); // Name, MaxSpeed, Consumption, TankVolume
	auto pAudi = std::make_unique<PKW>("Audi", 120.0, 15.0, 50.0);
	auto pBMX = std::make_unique<Fahrrad>("BMX", 25.0); // Name, MaxSpeed
	auto pBMX2 = std::make_unique<Fahrrad>("BMX2", 10.0); // Name, MaxSpeed

	// assign vehicles to the roads
	autobahn->vAnnahme(std::move(pBMW));
	landstrasse->vAnnahme(std::move(pAudi), 3.0);
	autobahn->vAnnahme(std::move(pBMX), 3.0);
	landstrasse->vAnnahme(std::move(pBMX2));

	//innerorts (BMX, BMW)
	//landstrasse (Audi, BMX2)


	// initialise the graphics
	int Koordinaten[] = {700, 250, 100, 250};
	bInitialisiereGrafik(800, 500);
	bZeichneStrasse("Inner", "Land", 500, 2, Koordinaten);

	bool bPkwAdded = false;

	for (dGlobaleZeit = 0; dGlobaleZeit <= 10.0 ; dGlobaleZeit += 0.3)
	{
		std::cout << "\nGlobale Zeit: " << dGlobaleZeit << std::endl;

		// update GUI time
		vSetzeZeit(dGlobaleZeit);

		if (!bPkwAdded && dGlobaleZeit >= 5.0) // At approx 5.0 hours
		{
			std::cout << "\n--- NEUES FAHRZEUG HINZUGEFUEGT (Smart) ---\n";
			auto pSmart = std::make_unique<PKW>("Smart", 100.0, 5.0, 30.0);
			// Add as parking, starts at 6.0
			autobahn->vAnnahme(std::move(pSmart), 6.0);
			bPkwAdded = true;
		}

		Fahrzeug::vKopf();
		std::cout << "-----------------------------------------------------------------------------------------------------------\n" ;
		autobahn->vSimulieren();
		landstrasse->vSimulieren();

		std::cout << std::endl;

		Weg::vKopf();
		std::cout << "-----------------------------------------------\n" ;
		std::cout << *autobahn << std::endl;
		std::cout << *landstrasse << std::endl;

		vSleep(200); // wait for animation
	}

	vBeendeGrafik();
}

void vAufgabe_6a()
{
	//creating a VListe
	vertagt::VListe<int> int_list;

	//defining range of random numbers generated
	static std::mt19937 device(0);
	std::uniform_int_distribution<int>dist(1,10);

	//appending generated numbers into the list
	for (int i = 0; i < 10; i++)
	{
		int zuf = dist(device);
		int_list.push_back(zuf);
	}

	//execute all the actions
	int_list.vAktualisieren();

	//print out the list of numbers
	std::cout << "Initial list: ";
	for (int num : int_list)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;

	//removing number greater than 5
	auto it = int_list.begin();
	while (it != int_list.end())
	{
		if (*it > 5)
		{
			int_list.erase(it);
		}
		++it;
	}

	int_list.vAktualisieren();

	//print out the list of numbers
	std::cout << "List (<= 5): ";
	for (int num : int_list)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;

	//add numbers to the beginning and the end of the list
	int_list.push_front(100);
	int_list.push_back(200);

	int_list.vAktualisieren();

	//print out the list of numbers
	std::cout << "Push_back and Push_front function test: ";
	for (int num : int_list)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
}

void vAufgabe_7()
{
    auto Kr1 = std::make_shared<Kreuzung>("Kr1");
    auto Kr2 = std::make_shared<Kreuzung>("Kr2", 100.0);
    auto Kr3 = std::make_shared<Kreuzung>("Kr3");
    auto Kr4 = std::make_shared<Kreuzung>("Kr4");

    // 2. Connect the Junctions (Create Roads)
    // Syntax: Source, Target, Name->, Name<-, Length, Limit, Ban

    // a) Kr1 <-> Kr2 (W12/W21)
    Kreuzung::vVerbinde("W12", "W21", 40.0, Tempolimit::Innerorts, true,Kr1, Kr2);

    // b) Kr2 <-> Kr3 (Parallel Roads)
    // Route A: Autobahn (Longer, Faster)
    Kreuzung::vVerbinde("W23a", "W32a", 115.0, Tempolimit::Autobahn, false, Kr2, Kr3);
    // Route B: Innerorts (Shorter, Slower, No Overtaking)
    Kreuzung::vVerbinde("W23b", "W32b", 40.0, Tempolimit::Innerorts, true, Kr2, Kr3);

    // c) Kr2 <-> Kr4
    Kreuzung::vVerbinde("W24", "W42", 55.0, Tempolimit::Innerorts, true,Kr2, Kr4);

    // d) Kr3 <-> Kr4
    Kreuzung::vVerbinde( "W34", "W43", 85.0, Tempolimit::Autobahn, false, Kr3, Kr4);

    // e) Kr4 <-> Kr4 (Loop)
    // Connecting a junction to itself creates a loop road
    Kreuzung::vVerbinde( "W44a", "W44b", 130.0, Tempolimit::Landstrasse, false, Kr4, Kr4);


    // 3. Create Vehicles
    // Place them on Kr1 to start driving
    auto f1 = std::make_unique<PKW>("Audi", 200, 10, 50); // Fast car
    auto f2 = std::make_unique<PKW>("BMW", 180, 8, 60);   // Another car
    auto f3 = std::make_unique<Fahrrad>("Bike", 25);      // Slow vehicle

    // Annahme at Kr1.
    // Note: Use smart pointers correctly (move ownership)
    Kr1->vAnnahme(std::move(f1), 0.0);
    Kr1->vAnnahme(std::move(f2), 1.0); // Starts 1 hour later
    Kr1->vAnnahme(std::move(f3), 2.0); // Starts 2 hours later


    // 4. Graphics Setup (Optional, but recommended for visual verification)
    bInitialisiereGrafik(1000, 600);

    // Draw Junctions (Approximate coordinates based on the image grid)
    bZeichneKreuzung(680, 40);  // Kr1 (Top Right)
    bZeichneKreuzung(680, 300); // Kr2 (Center Right)
    bZeichneKreuzung(680, 570); // Kr3 (Bottom Right)
    bZeichneKreuzung(320, 300); // Kr4 (Center Left)

    // Draw Streets (Coordinates: x1, y1, x2, y2, ...)
    int s1[] = {680, 40, 680, 300}; // W12
    bZeichneStrasse("W12", "W21", 40, 2, s1);

    int s2[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
    bZeichneStrasse("W23a", "W32a", 115, 6, s2);

    // Parallel Roads Kr2 <-> Kr3
    int s3[] = {680, 300, 680, 570}; // Straight line for W23b
    bZeichneStrasse("W23b", "W32b", 40, 2, s3);

    int s4[] = {680, 300, 320, 300}; // W24
    bZeichneStrasse("W24", "W42", 55, 2, s4);

    int s5[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300}; // W34
    bZeichneStrasse("W34", "W43", 85, 5, s5);

    // Loop at Kr4
    int s6[] = {320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300};
    bZeichneStrasse("W44a", "W44b", 130, 7, s6);


    // 5. Simulation Loop
    for (dGlobaleZeit = 0; dGlobaleZeit < 20.0; dGlobaleZeit += 0.25)
    {
        std::cout << "\n--------------------------------------" << std::endl;
        std::cout << "Globale Zeit: " << dGlobaleZeit << std::endl;

        vSetzeZeit(dGlobaleZeit);

        Fahrzeug::vKopf();
        // Simulate all Junctions (which simulate their roads)
        Kr1->vSimulieren();
        Kr2->vSimulieren();
        Kr3->vSimulieren();
        Kr4->vSimulieren();

        vSleep(1000);
    }

    vBeendeGrafik();
}

void vAufgabe_8()
{
	std::ifstream infile("VO.dat");

	if (!infile.is_open())
	{
		std::cerr << "Fehler: Datei konnte nicht geoeffnet werden!" << std::endl;
		return;
	}

	std::unique_ptr<PKW> pkw = std::make_unique<PKW>("", 2.0,1.0);
	std::unique_ptr<Fahrrad> fahrrad = std::make_unique<Fahrrad>("", 0.0);
	std::unique_ptr<Kreuzung> kreuzung = std::make_unique<Kreuzung>("", 0.0);

	try
	{
		infile.exceptions(std::ios::failbit | std::ios::badbit);

		infile>>*pkw;
		infile>>*fahrrad;
		infile>>*kreuzung;
	}
	catch (const std::ios_base::failure& e)
	{
		// Specific catch for stream errors
		std::cerr << "File Error (Stream): " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		// General catch for other errors (like logic_error from your vEinlesen)
		std::cerr << "Standard Error: " << e.what() << std::endl;
	}

	std::cout<< pkw->getName() << "  "
			<< pkw->getMaxGeschwindigkeit() << "  "
			<< pkw->getVerbrauch() << "  "
			<< pkw->getTankvolumen() << "  "
			<< std::endl;
	std::cout<< fahrrad->getName() << "  "
			<< fahrrad->getMaxGeschwindigkeit() << "  "
			<< std::endl;
	std::cout<< kreuzung->getName() << "  "
			<< kreuzung->getTankstelle()<< std::endl;
}

void vAufgabe_9()
{
	std::ifstream infile("Simu.dat");

	if (!infile.is_open())
	{
		std::cerr << "Fehler: Datei konnte nicht geoeffnet werden!" << std::endl;
		return;
	}
	try
	{
		std::cout << "Starte Einlesen der Simulation..." << std::endl;

		Simulation sim;

		sim.vEinlesen(infile,false);

		std::cout << "Einlesen erfolgreich. Starte Simulation..." << std::endl;

		sim.vSimulieren(10.0, 0.25);

		std::cout << "Simulation beendet." << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "FEHLER waehrend der Simulation: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unbekannter Fehler aufgetreten." << std::endl;
	}
}

void vAufgabe_9a()
{
	std::ifstream infile("SimuDisplay.dat");

	if (!infile.is_open())
	{
		std::cerr << "Fehler: Datei konnte nicht geoeffnet werden!" << std::endl;
		return;
	}
	try
	{		bInitialisiereGrafik(1000, 1000);

			std::cout << "Starte Einlesen der Simulation..." << std::endl;

			Simulation sim;

			sim.vEinlesen(infile,true);

			std::cout << "Einlesen erfolgreich. Starte Simulation..." << std::endl;

			sim.vSimulieren(10.0, 0.25);

			std::cout << "Simulation beendet." << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << "FEHLER waehrend der Simulation: " << e.what() << std::endl;
		}
		catch (...)
		{
			std::cerr << "Unbekannter Fehler aufgetreten." << std::endl;
		}
}
