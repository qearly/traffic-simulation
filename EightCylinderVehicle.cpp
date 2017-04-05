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


#include "EightCylinderVehicle.h"
#include "TrafficLight.h"
#include "Map.h"
#include "Road.h"
#include <stdlib.h>
#include <sys/types.h>    
#include <sys/timeb.h>     
#include <time.h>

using namespace std;

EightCylinderVehicle::EightCylinderVehicle()
{

	carID = 0;
	direction = 0.0;
	Acceleration = 0.0;
	speedMPH = 0.0;
	speedMPS = 0.0;
	xVehicleLocation = 0.0;
	yVehicleLocation = 0.0;
}

EightCylinderVehicle::~EightCylinderVehicle()
{

}

void EightCylinderVehicle::PrintStatus()
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

void EightCylinderVehicle::setType(char * name)
{
	strcpy(type, name);
}

void EightCylinderVehicle::setCarID(int ID)
{
	carID = ID;
}

char *EightCylinderVehicle::getType()
{
	return type;
}

int EightCylinderVehicle::getCarID()
{
	return carID;
}

void EightCylinderVehicle::setDirection(double direc)
{
	direction = direc;
}

void EightCylinderVehicle::setAcceleration(double inputAcceleration)
{
	Acceleration = inputAcceleration;
}

void EightCylinderVehicle::setSpeedMPS(double speed)
{
	speedMPS = speed;
}

void EightCylinderVehicle::setSpeedMPH(double speed)
{
	speedMPH = speed;
}

void EightCylinderVehicle::setxVehicleLocation(double location)
{
	xVehicleLocation = location;
}

void EightCylinderVehicle::setyVehicleLocation(double location)
{
	yVehicleLocation = location;
}

double EightCylinderVehicle::getSpeedMPS()
{
	return speedMPS;
}

double EightCylinderVehicle::getSpeedMPH()
{
	return speedMPH;
}

double EightCylinderVehicle::getDirection()
{
	return direction;
}

double EightCylinderVehicle::getAcceleration()
{
	return Acceleration;
}

double EightCylinderVehicle::getxVehicleLocation()
{
	return xVehicleLocation;
}

double EightCylinderVehicle::getyVehicleLocation()
{
	return yVehicleLocation;
}

