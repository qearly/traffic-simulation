/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: Main.cpp
*   Author: Matt Stewart
*   Desc: Main.
*   Date: 4-8-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/


#include "Simulation.h"
#include "VehicleFactory.h"
#include "TrafficSimDataParser.h"


using namespace std;

int main()
{


	Simulation *sim = new Simulation();

	if (sim->initSimulation())
	{
		sim->runSimulation();
	}

	cin.ignore();
	cout << "Press Enter to exit." << endl;
	cin.get();

	return 0;
}
