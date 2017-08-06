/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Simulation.cpp
*   Author: Matt Stewart
*   Desc: Initializing the other classes, running the sim.
*   Date: 3-19-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/


#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 

#include <vector>
#include "Simulation.h"
#include "TrafficSimDataParser.h"
#include <sys/types.h>     
#include <sys/timeb.h>     
#include <time.h> 
#include <iostream>

using namespace std;

Simulation::Simulation()
{
	simSpeed = 0;
	lightInst = new TrafficLightManager();
}

Simulation::~Simulation()
{
	
}

bool Simulation::initSimulation()
{
	cout << "=============================================================" << endl;
	cout << "|      			Traffic Simulation    		    |" << endl;
	cout << "|              CS 307 Programming Assignment 2              |" << endl;
	cout << "=============================================================" << endl;
	cout << endl;
	cout << "Enter the the simulation data file and press enter:" << endl;
	cout << "\t";
	char filename[64];
	cin >> filename;
	cout << endl;
	
	TrafficSimDataParser *dp = TrafficSimDataParser::getInstance();
	dp->setDataFileName(filename);
	Vehicle *vehicle = new Vehicle();
	Map *mapInst = new Map(filename);

	char carType[64];
	int carID = 0;
	double xPosition = 0.0;
	double yPosition = 0.0;
	double startDir = 0.0;
	double acc = 0.0;

	if (dp->getVehicleData(carType, &carID, &xPosition, &yPosition, &startDir, &acc))
	{

		vehicle->setType(carType);
		vehicle->setCarID(carID);
		vehicle->setxVehicleLocation(xPosition);
		vehicle->setyVehicleLocation(yPosition);
		vehicle->setDirection(startDir);
		vehicle->setAcceleration(acc);

		vCollect.push_back(vehicle);
	}

	return true;
}

void Simulation::runSimulation()
{
	char filename[64];
	getSimSpeed();
	cout << "Now enter the name of the same data file one more time to get our vehicle moving: ";
	cin >> filename;
	cout << endl << endl;
	cout << "Creating Roads, Vehicles, and Intersections..." << endl;
	cout << endl;
	int i = 0;
	int counter = 0;

	_ftime(&tStruct);	
	thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); 
	outputTime = (thisTime + 5.0); 

	while (true)     
	{
		_ftime(&tStruct);    
		thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); 
					
		if (simSpeed == 1)
		{
			while (i < 5)
			{
				// Intersection object updates each traffic light at the end of the Move function, so only necessary to call Move here
				vCollect[0]->CallMove(filename);
				lightInst->UpDate();
				i++;
			}
		}

		else if (simSpeed == 2)
		{
			while (i < 10)
			{
				// Same
				vCollect[0]->CallMove(filename);
				lightInst->UpDate();
				i++;
			}
		}

		else if (simSpeed == 5)
		{
			while (i < 25)
			{
				// Same
				vCollect[0]->CallMove(filename);
				lightInst->UpDate();
				i++;
			}
		}

					
												
		if (thisTime >= outputTime)
		{
			counter += (5 * simSpeed);
			cout << "Total time: " << counter << endl;
			PrintReport();

			outputTime += 5.0; 
			i = 0;
		}

	}

	
	
}

void Simulation::PrintReport()
{
	vCollect[0]->CallPrintStatus();
	lightInst->PrintLight();
}

void Simulation::getSimSpeed()
{
	cout << "This program can run in 1X, 2X, or 5X. Which would you like?" << endl;
	cout << "Enter the number only and press enter: " << endl;
	cin >> simSpeed;
}
