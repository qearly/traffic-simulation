#include "includes.h"

using namespace std;

void Vehicle::Move(Road *roadInst, Intersetion *intersectInst)
{
	// Adjusted x and y locations as the vehicle is moving
	double newX = 0;
	double newY = 0;

	double laneWidth = 36.6;
	double BD = ((roadInst->getLaneNumber()) == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
	double distToCenter = intersectInst->getxCenterPoint() - xVehicleLocation;
	double distAfterTurn = speedMPS - distToCenter - BD;

	// If direction is East
	if (direction == 0.0)
	{
		newX = xVehicleLocation + speedMPS;
		newY = yVehicleLocation;
	}

	// If direction is North
	else if (direction == 90.0)
	{
		newX = xVehicleLocation;
		newY = yVehicleLocation - speedMPS;
	}

	// If direction is West
	else if (direction == 180.0)
	{
		newX = xVehicleLocation - speedMPS;
		newY = yVehicleLocation;
	}

	// If direction is North
	else if (direction == 270.0)
	{
		newX = xVehicleLocation;
		newY = yVehicleLocation + speedMPS;
	}
}

void Vehicle::PrintReport()
{

}

void Vehicle::updateVehicleSpeed(double mps, double mph)
{
	double laneWidth = 36.6;
	double BC = ((roadInst->getLaneNumber()) == 4) ? (laneWidth * 2.0) : (laneWidth * 1.0);
	double AC = intersectInst->getxCenterPoint() - intersectInst->getyCenterPoint();
	double distNextIntersection = AC - BC;
	double speedLimitMPS = roadInst->getSpeedLimitMPS();
	double speedLimitMPH = roadInst->getSpeedLimitMPH();
	double stopDist = 1.1 * speedMPH + 0.06 * pow(speedMPH, 2);

	// Becai\use it's returning an enum I am not yet sure how to set this to a variable
	lightInst->getEWState();

	if ((lightInst->getEWState() == RED) || (lightInst->getEWState() == YELLOW))
	{
		if (stopDist < distNextIntersection)
		{
			if (speedMPS < speedLimitMPS)
			{
				speedMPS += Acceleration;
				speedMPH += speedMPS / 0.44704;
				if (speedMPS > speedLimitMPS)
				{
					speedMPS = speedLimitMPS;
					speedMPH = speedMPS / 0.44704;
				}
			}
		}
		
		else if ((stopDist > distNextIntersection) && (speedMPS != 0))
		{
			while ((stopDist > distNextIntersection) && (distNextIntersection > laneWidth) && (speedMPS > 0))
			{
				speedMPS -= Acceleration;
				speedMPH = speedMPS / 0.44704;
				if (speedMPS < 0)
				{
					speedMPS = 0;
					speedMPH = 0;
				}
				distNextIntersection = stopDist = 1.1 * speedMPH + 0.06 * pow(speedMPH, 2);
				distNextIntersection *= 0.3048;
				if (speedMPS == 0)
				{
					break;
				}
			}

			if (distNextIntersection < laneWidth)
			{
				speedMPS = 0;
				speedMPH = 0;
			}
		 }

		else
		{
			if (speedMPS < speedLimitMPS)
			{
				speedMPS += Acceleration;
				speedMPH = speedMPS / 0.44704;
				if (speedMPS > speedLimitMPS)
				{
					speedMPS = speedLimitMPS;
					speedMPH = speedMPS / 0.44704;
				}
			}
		}

		setSpeedMPS(speedMPS);
		setSpeedMPH(speedMPH);
	}
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

