#include "includes.h"

using namespace std;

void Vehicle::Move()
{

}

void Vehicle::PrintReport()
{

}

void Vehicle::setVehicleSpeed(double mps, double mph)
{

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

void Vehicle::setxVehicleStartPoint(double start)
{
	xVehicleStartPoint = start;
}

void Vehicle::setyVehicleStartPoint(double start)
{
	yVehicleStartPoint = start;
}

void Vehicle::setStartDirection(int start)
{
	startDirection = start;
}

void Vehicle::setAcceleration(double inputAcceleration)
{
	Acceleration = inputAcceleration;
}

void Vehicle::setSpeedMPS(double speed)
{
}

void Vehicle::setSpeedMPH(double speed)
{
	speedMPH = speed;
}

void Vehicle::setSpeedMPS(double speed)
{
	speedMPS = speed;
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

double Vehicle::getxVehicleStartPoint()
{
	return xVehicleStartPoint;
}

double Vehicle::getyVehicleStartPoint()
{
	return yVehicleStartPoint;
}

int Vehicle::getStartDirection()
{
	return startDirection;
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

