
/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: Vehicle.cpp
*   Author: Matt Stewart
*   Desc: Info on vehicle, and a move function that handles all vehicle movement.
*   Date: 4-8-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/


#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 

#include "Vehicle.h"
#include "FourCylinderMovement.h"
#include "TrafficLightManager.h"
#include "Map.h"
#include "Road.h"
#include <stdlib.h>
#include <sys/types.h>    
#include <sys/timeb.h>     
#include <time.h>

using namespace std;

Vehicle::Vehicle()
{

	carID = 0;
	direction = 0.0;
	Acceleration = 0.0;
	speedMPH = 0.0;
	speedMPS = 0.0;
	xVehicleLocation = 0.0;
	yVehicleLocation = 0.0;
	fourVehicle = new FourCylinderMovement();
	sixVehicle = new SixCylinderMovement();
	eightVehicle = new EightCylinderMovement();
	wheelerVehicle = new WheelerMovement();
	truckVehicle = new TruckMovement();
	
}

Vehicle::~Vehicle()
{

}

void Vehicle::CallMove(char *filename)
{
	fourVehicle->Move(filename);
	sixVehicle->Move(filename);
	eightVehicle->Move(filename);
	truckVehicle->Move(filename);
	wheelerVehicle->Move(filename);
}

void Vehicle::CallPrintStatus()
{
	
	fourVehicle->PrintStatus();
	sixVehicle->PrintStatus();
	eightVehicle->PrintStatus();
	wheelerVehicle->PrintStatus();
	truckVehicle->PrintStatus();

}

void Vehicle::setType(char * name)
{
	strcpy(type, name);
}

void Vehicle::setCarID(int ID)
{
	carID = ID;
}

char *Vehicle::getType()
{
	return type;
}

int Vehicle::getCarID()
{
	return carID;
}

void Vehicle::setDirection(double direc)
{
		direction = direc;
}

void Vehicle::setAcceleration(double inputAcceleration)
{
	Acceleration = inputAcceleration;
}

void Vehicle::setSpeedMPS(double speed)
{
	speedMPS = speed;
}

void Vehicle::setSpeedMPH(double speed)
{
	speedMPH = speed;
}

void Vehicle::setxVehicleLocation(double location)
{
	xVehicleLocation = location;
}

void Vehicle::setyVehicleLocation(double location)
{
	yVehicleLocation = location;
}

double Vehicle::getSpeedMPS()
{
	return speedMPS;
}

double Vehicle::getSpeedMPH()
{
	return speedMPH;
}

double Vehicle::getDirection()
{
	return direction;
}

double Vehicle::getAcceleration()
{
	return Acceleration;
}

double Vehicle::getxVehicleLocation()
{
	return xVehicleLocation;
}

double Vehicle::getyVehicleLocation()
{
	return yVehicleLocation;
}


