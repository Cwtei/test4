/*
 * Simulation.cpp
 *
 *  Created on: Nov 26, 2025
 *      Author: cw
 */

#include "Simulation.h"
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

#include "Tempolimit.h"

Simulation::Simulation()
{}

Simulation::~Simulation()
{}

void Simulation::vEinlesen(std::istream& in, bool bMitGrafik)
{
    std::string sKeyword;
    int iZeile = 0; //Line counter

    while (in >> sKeyword) //in>>sKeyword return the bool true when reading of data is successful
    {
        iZeile++; //increase Zeile by 1
        try
        {
            if (sKeyword == "KREUZUNG")
            {
                auto pKreuzung = std::make_shared<Kreuzung>("", 0.0); //Kreuzung erzeugen

                in >> *pKreuzung; //Daten einlesen

                //Check if the kreuzung existed
                if (p_mKreuzungen.find(pKreuzung->getName()) != p_mKreuzungen.end()) //if its found, iterator will not be end(), instead it will be some other positions
                {
                    throw std::runtime_error("Kreuzung existiert bereits: " + pKreuzung->getName());
                }

                if (bMitGrafik)
                {
                    int x, y;
                    in >> x >> y; // Read coordinates
                    bZeichneKreuzung(x, y); // Draw
                }

                p_mKreuzungen[pKreuzung->getName()] = pKreuzung; //store the data in the map
            }
            else if (sKeyword == "STRASSE")
            {
                // Format: QuellName ZielName WegNameHin WegNameRueck Laenge Limit Ueberholverbot
                std::string sNameQ, sNameZ, sNameW1, sNameW2;
                double dLaenge;
                int iLimit;
                int bUeberholverbot;

                in >> sNameQ >> sNameZ >> sNameW1 >> sNameW2 >> dLaenge >> iLimit >> bUeberholverbot;

                // 1. Find Source and Target Junctions
                auto itQ = p_mKreuzungen.find(sNameQ);
                auto itZ = p_mKreuzungen.find(sNameZ);

                if (p_mKreuzungen.find(sNameQ) == p_mKreuzungen.end())
                {
                	throw std::runtime_error("Quellkreuzung nicht gefunden: " + sNameQ);
                }
                if (itZ == p_mKreuzungen.end())
                {
                	throw std::runtime_error("Zielkreuzung nicht gefunden: " + sNameZ);
                }

                bool verbot;
                switch (bUeberholverbot){
                case 0:
                	verbot = false;
                	break;
                case 1:
                	verbot = true;
                	break;
                default:
                	throw std::runtime_error("Ungueltige Ueberholverbot.");
                }

               Tempolimit temp;
               switch (iLimit){
               case 1:
            	  temp = Tempolimit::Innerorts;
            	  break;
               case 2:
            	   temp = Tempolimit::Landstrasse;
            	   break;
               case 3:
            	   temp = Tempolimit::Autobahn;
            	   break;
               default:
            	   throw std::runtime_error("Ungueltige Tempolimit.");
               }
                // 2. Connect them (Creates 2 Roads)
                Kreuzung::vVerbinde(sNameW1, sNameW2, dLaenge, temp, verbot, itQ->second, itZ->second);

                if (bMitGrafik)
                {
                    int iAnzahl;
                    in >> iAnzahl; // Number of coordinate pairs

                    int* pCoordinates = new int[2 * iAnzahl]; // Dynamic array for API
                    for (int i = 0; i < 2 * iAnzahl; i++)
                    {
                        in >> pCoordinates[i];
                    }

                    // Draw both directions
                    bZeichneStrasse(sNameW1, sNameW2, (int)dLaenge, iAnzahl, pCoordinates);

                    delete[] pCoordinates; // Clean up
                }}
            else if (sKeyword == "PKW" || sKeyword == "FAHRRAD")
            {
                // 1. Create Vehicle
                std::unique_ptr<Fahrzeug> pFzg;
                if (sKeyword == "PKW")
                {
                	pFzg = std::make_unique<PKW>("", 0.0, 0.0);
                }
                else
                {
                	pFzg = std::make_unique<Fahrrad>("", 0.0);
                }

                // 2. Read Vehicle Data
                in >> *pFzg;

                // 3. Read Start Info (Junction Name, Start Time)
                std::string sNameStart;
                double dStartZeit;
                in >> sNameStart >> dStartZeit;

                // 4. Find Start Junction
                auto itStart = p_mKreuzungen.find(sNameStart);
                if (itStart == p_mKreuzungen.end())
                {
                    throw std::runtime_error("Startkreuzung nicht gefunden: " + sNameStart);
                }

                // 5. Place Vehicle (vAnnahme transfers ownership)
                itStart->second->vAnnahme(std::move(pFzg), dStartZeit);
            }
            else
            {
                throw std::runtime_error("Unbekanntes Schlusselwort: " + sKeyword);
            }
        }
        catch (const std::exception& e)
        {
        	// Add line number context and rethrow [cite: 58547-58549]
            throw std::runtime_error("Fehler in Zeile " + std::to_string(iZeile) + ": " + e.what());
        }
    }
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
    // Run the global simulation loop
    for (dGlobaleZeit = 0; dGlobaleZeit <= dDauer; dGlobaleZeit += dZeitschritt)
    {
        // Set time for graphics
        vSetzeZeit(dGlobaleZeit);

        std::cout << "Globale Zeit: " << dGlobaleZeit <<std::endl;

        Fahrzeug::vKopf();

        // Simulate all junctions (which simulate their roads/vehicles)
        for (auto& pair : p_mKreuzungen)
        {
            pair.second->vSimulieren();
        }

        vSleep(100);
        std::cout<<std::endl;
    }
}
