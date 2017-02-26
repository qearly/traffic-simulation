#include "Vehicle.h"

using namespace std;

void Vehicle::Move()
{

}

void Vehicle::PrintReport()
{

}

void Vehicle::setType(string name)
{
	type = name;
}

void Vehicle::setCarID(int ID)
{
	carID = ID;
}

string Vehicle::getType()
{
	return type;
}

int Vehicle::getCarID()
{
	return carID;
}

void Vehicle::setxIntersectStartPoint(double start)
{
	xIntersectStartPoint = start;
}

void Vehicle::setyIntersectStartPoint(double start)
{
	yIntersectStartPoint = start;
}

void Vehicle::setIntersectStartDirection(int start)
{
	intersectStartDirection = start;
}

void Vehicle::setIntersectAcceleration(double acceleration)
{
	intersectAcceleration = acceleration;
}

void Vehicle::setIntersectSpeed(double speed)
{
	intersectSpeed = speed;
}

void Vehicle::setxIntersectLocation(double location)
{
	xIntersectLocation = location;
}

void Vehicle::setyIntersectLocation(double location)
{
	yIntersectLocation = location;
}

double Vehicle::getxIntersectionStartPoint()
{
	return xIntersectStartPoint;
}

double Vehicle::getyIntersectionStartPoint()
{
	return yIntersectStartPoint;
}

int Vehicle::getIntersectStartDirection()
{
	return intersectStartDirection;
}

double Vehicle::getIntersectAcceleration()
{
	return intersectAcceleration;
}

double Vehicle::getIntersectSpeed()
{
	return intersectSpeed;
}

double Vehicle::getxIntersectLocation()
{
	return xIntersectLocation;
}

double Vehicle::getyIntersectLocation()
{
	return yIntersectLocation;
}
