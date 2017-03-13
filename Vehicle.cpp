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
	double newXIfTurn = intersectInst->getxCenterPoint() - distAfterTurn;
	double newYIfTurn = yVehicleLocation + distAfterTurn;

	bool turnDecided = false;
	Intersection *nextIntersection = new Intersection();
	Intersection *curIntersection = new Intersection();
	Map *mapInst = new Map();

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

	else
	{
		cout << "Something is wrong (first set of if statements, Move() function. We should not be here." << endl;
	}

	char name[64];
	strcpy(name, roadInst->getRoadName());

	if (name == NULL)
	{
		if (direction == 0.0)
		{
			xVehicleLocation = xVehicleLocation + laneWidth * 2.0;
		}

		else if (direction = 90.0)
		{
			yVehicleLocation = yVehicleLocation - laneWidth * 2.0;
		}

		else if (direction = 180.0)
		{
			xVehicleLocation = xVehicleLocation - laneWidth * 2.0;
		}

		else if (direction = 270.0)
		{
			yVehicleLocation = yVehicleLocation + laneWidth * 2.0;
		}
		
		else
		{
			cout << "Something is wrong (second set of if statements, Move() function). We should not be here." << endl;
		}

		strcpy(name, roadInst->getRoadName());

		if (name == NULL)
		{
			cout << "This program is not working. Terminate." << endl;
			throw std::exception();
		}

		else
		{
			cout << "Everything might be fine." << endl;
		}
	}

	nextIntersection = mapInst->getNextIntersection(xVehicleLocation, yVehicleLocation, direction, intersectInst);

	if (nextIntersection == NULL)
	{
		curIntersection = mapInst->getIntersection(intersectID);
		intersection->getxCenterPoint();
		intersection->getyCenterPoint();

		if (direction == 0.0)
		{
			if (turnDirection == LEFT)
			{
				Road *tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesEW / 2) * laneWidth;

				direction = 90.0;
			}

			else if (turnDirection == RIGHT)
			{
				Road *tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesEW / 2) * laneWidth;

				direction = 270.0;
			}
		}

		else if (direction == 90.0)
		{
			if (turnDirection == LEFT)
			{
				Road *tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesEW == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesNS / 2) * laneWidth;

				direction = 0.0;
			}

			else if (turnDirection == RIGHT)
			{
				Road *tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesEW == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesNS / 2) * laneWidth;

				direction = 170.0;
			}
		}
	}

	roadInst->getSpeedLimitMPH();
	roadInst->getSpeedLimitMPS();

	if (turnDecided == false)
	{
		// Decide turn at next intersection
		// set turnDecided to true
	}

	// If direction is North/South, get state of light
	if (direction == 90.0 || direction == 270.0)
	{
		lightInst->getNSState();
	}

	// If direction is East/West, get state of light
	else if (direction == 0.0 || direction == 180.0)
	{
		lightInst->getEWState();
	}

	updateVehicleSpeed(speedMPS, speedMPH, roadInst, intersectInst, lightInst);
	nextIntersection->getxCenterPoint();
	nextIntersection->getyCenterPoint();

	if (direction == 0.0)
	{
		// Sigh
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

