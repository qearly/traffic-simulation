/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Vehicle.cpp
*   Author: Matt Stewart
*   Desc: Info on vehicle, and a move function that handles all vehicle movement.
*   Date: 3-19-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/


#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 


#include "4CylinderVehicle.h"
#include "TrafficLight.h"
#include "Map.h"
#include "Road.h"
#include <stdlib.h>
#include <sys/types.h>    
#include <sys/timeb.h>     
#include <time.h>

using namespace std;

FourCylinderVehicle::FourCylinderVehicle()
{

	carID = 0;
	direction = 0.0;
	Acceleration = 0.0;
	speedMPH = 0.0;
	speedMPS = 0.0;
	xVehicleLocation = 0.0;
	yVehicleLocation = 0.0;
}

FourCylinderVehicle::~FourCylinderVehicle()
{

}

void FourCylinderVehicle::PrintStatus()
{

	cout << "Vehicle type: " << type << endl;
	cout << "Vehicle is currently traveling along " << road->getRoadName() << "." << endl;
	cout << "Vehicle is driving at " << direction << " degrees, going a speed of " << speedMPH << " MPH." << endl;
	cout << "The current location of Vehicle is at these X/Y coordinates: (" << xVehicleLocation << ", " << yVehicleLocation << ")" << endl;

	if (light->getNSState() == 0)
	{
		cout << "North/South traffic lights are currently GREEN" << endl;
	}

	else if (light->getNSState() == 1)
	{
		cout << "North/South traffic lights are currently RED" << endl;
	}

	else if (light->getNSState() == 2)
	{
		cout << "North/South traffic lights are currently YELLOW" << endl;
	}

	if (light->getEWState() == 0)
	{
		cout << "East/West traffic lights are currently GREEN" << endl;
	}

	else if (light->getEWState() == 1)
	{
		cout << "East/West traffic lights are currently RED" << endl;
	}

	else if (light->getEWState() == 2)
	{
		cout << "East/West traffic lights are currently YELLOW" << endl;
	}

	cout << endl << endl << endl;
}

void FourCylinderVehicle::setType(char * name)
{
	strcpy(type, name);
}

void FourCylinderVehicle::setCarID(int ID)
{
	carID = ID;
}

char *FourCylinderVehicle::getType()
{
	return type;
}

int FourCylinderVehicle::getCarID()
{
	return carID;
}

void FourCylinderVehicle::setDirection(double direc)
{
	direction = direc;
}

void FourCylinderVehicle::setAcceleration(double inputAcceleration)
{
	Acceleration = inputAcceleration;
}

void FourCylinderVehicle::setSpeedMPS(double speed)
{
	speedMPS = speed;
}

void FourCylinderVehicle::setSpeedMPH(double speed)
{
	speedMPH = speed;
}

void FourCylinderVehicle::setxVehicleLocation(double location)
{
	xVehicleLocation = location;
}

void FourCylinderVehicle::setyVehicleLocation(double location)
{
	yVehicleLocation = location;
}

double FourCylinderVehicle::getSpeedMPS()
{
	return speedMPS;
}

double FourCylinderVehicle::getSpeedMPH()
{
	return speedMPH;
}

double FourCylinderVehicle::getDirection()
{
	return direction;
}

double FourCylinderVehicle::getAcceleration()
{
	return Acceleration;
}

double FourCylinderVehicle::getxVehicleLocation()
{
	return xVehicleLocation;
}

double FourCylinderVehicle::getyVehicleLocation()
{
	return yVehicleLocation;
}

