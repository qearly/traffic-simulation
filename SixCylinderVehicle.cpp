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


#include "SixCylinderVehicle.h"
#include "TrafficLight.h"
#include "Map.h"
#include "Road.h"
#include <stdlib.h>
#include <sys/types.h>    
#include <sys/timeb.h>     
#include <time.h>

using namespace std;

SixCylinderVehicle::SixCylinderVehicle()
{

	carID = 0;
	direction = 0.0;
	Acceleration = 0.0;
	speedMPH = 0.0;
	speedMPS = 0.0;
	xVehicleLocation = 0.0;
	yVehicleLocation = 0.0;
}

SixCylinderVehicle::~SixCylinderVehicle()
{

}

void SixCylinderVehicle::PrintStatus()
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

void SixCylinderVehicle::setType(char * name)
{
	strcpy(type, name);
}

void SixCylinderVehicle::setCarID(int ID)
{
	carID = ID;
}

char *SixCylinderVehicle::getType()
{
	return type;
}

int SixCylinderVehicle::getCarID()
{
	return carID;
}

void SixCylinderVehicle::setDirection(double direc)
{
	direction = direc;
}

void SixCylinderVehicle::setAcceleration(double inputAcceleration)
{
	Acceleration = inputAcceleration;
}

void SixCylinderVehicle::setSpeedMPS(double speed)
{
	speedMPS = speed;
}

void SixCylinderVehicle::setSpeedMPH(double speed)
{
	speedMPH = speed;
}

void SixCylinderVehicle::setxVehicleLocation(double location)
{
	xVehicleLocation = location;
}

void SixCylinderVehicle::setyVehicleLocation(double location)
{
	yVehicleLocation = location;
}

double SixCylinderVehicle::getSpeedMPS()
{
	return speedMPS;
}

double SixCylinderVehicle::getSpeedMPH()
{
	return speedMPH;
}

double SixCylinderVehicle::getDirection()
{
	return direction;
}

double SixCylinderVehicle::getAcceleration()
{
	return Acceleration;
}

double SixCylinderVehicle::getxVehicleLocation()
{
	return xVehicleLocation;
}

double SixCylinderVehicle::getyVehicleLocation()
{
	return yVehicleLocation;
}

