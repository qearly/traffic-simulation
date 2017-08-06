/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Simulation.h
*   Author: Matt Stewart
*   Desc: Simulation header file
*   Date: 3-19-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/

#pragma once
#include "Vehicle.h"
#include "Map.h"
#include "Intersection.h"
#include "TrafficLightManager.h"
#include <vector>

class Simulation
{
private:
	int simSpeed;
	struct _timeb tStruct;
	double thisTime;
	double outputTime;
	bool done;
	Map *roadMap;
	Intersection *intersectInst;
	Road *roadInst;
	TrafficLightManager *lightInst;
	vector<Vehicle*>vCollect;

public:
	Simulation();
	~Simulation();
	bool initSimulation();
	void runSimulation();
	void PrintReport();
	void getSimSpeed();
};