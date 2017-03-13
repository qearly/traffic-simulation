#include "includes.h"
#include "TrafficLight.h"
#include "Map.h"
#include "Road.h"

using namespace std;

Vehicle::Vehicle()
{
	type = NULL;
	carID = 0;
	xVehicleStartPoint = 0.0;
	yVehicleStartPoint = 0.0;
	direction = 0.0;
	Acceleration = 0.0;
	speedMPH = 0.0;
	speedMPS = 0.0;
	xVehicleLocation = 0.0;
	yVehicleLocation = 0.0;
}

Vehicle::~Vehicle()
{
	delete[] type;
}

void Vehicle::Move(Road *roadInst, Intersection *intersectInst, TrafficLight *lightInst)
{
	// This might work. Think about it.
	// Something is not right with the way i'm thinking about this. It's frustrating.
	char roadName[64];
	char filename[64];
	int intersectID = 0;
	TrafficSimDataParser *simInst = new TrafficSimDataParser(filename);
	Map *mapInst = new Map(simInst, roadName, &intersectID);
	Road *road = mapInst->getRoad(roadName);
	Intersection *intersection = mapInst->getIntersection(intersectID);
	// End of testing new stuff



	// Adjusted x and y locations as the vehicle is moving
	double newX = 0;
	double newY = 0;

	double laneWidth = 36.6;
	double BD = ((road->getLaneNumber()) == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
	double distToCenter = intersection->getxCenterPoint() - xVehicleLocation;
	double distAfterTurn = speedMPS - distToCenter - BD;
	double newXIfTurn = intersection->getxCenterPoint() - distAfterTurn;
	double newYIfTurn = yVehicleLocation + distAfterTurn;
	double AD = 0;


	// FOR SETTING VEHICLE SPEED
	double BC = ((road->getLaneNumber()) == 4) ? (laneWidth * 2.0) : (laneWidth * 1.0);
	double AC = intersection->getxCenterPoint() - intersection->getyCenterPoint();
	double distNextIntersection = AC - BC;

	// Meters per second
	double speedLimitMPS = road->getSpeedLimitMPS();

	// Miles per hour
	double speedLimitMPH = road->getSpeedLimitMPH();
	double stopDist = 1.1 * speedMPH + 0.06 * pow(speedMPH, 2);
	// END FOR SETTING VEHICLE SPEED

	bool turnDecided = false;

	// Some necessary objects
	Intersection *nextIntersection = new Intersection();
	Intersection *curIntersection = new Intersection();
	Road *tempRoad = new Road();

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
		cout << "Something is wrong (first set of if statements, Move() function). We should not be here." << endl;
	}

	if (road == NULL)
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

		if (road == NULL)
		{
			cout << "This program is not working. Terminate." << endl;
			throw std::exception();
		}

		else
		{
			cout << "Everything might be fine." << endl;
		}
	}

	nextIntersection = mapInst->getNextIntersection(xVehicleLocation, yVehicleLocation, direction);

	// HANDLING RARE EXCEPTION -- SEE LAST SLIDE
	if (nextIntersection == NULL)
	{
		curIntersection = mapInst->getIntersection(intersectID);
		intersection->getxCenterPoint();
		intersection->getyCenterPoint();

		if (direction == 0.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesEW / 2) * laneWidth;

				direction = 90.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
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
				tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesEW == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesNS / 2) * laneWidth;

				direction = 0.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesEW == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesNS / 2) * laneWidth;

				direction = 180.0;
			}
		}

		else if (direction == 180.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesEW / 2) * laneWidth;

				direction = 270.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesEW / 2) * laneWidth;

				direction = 90.0;
			}
		}

		else if (direction == 270.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesEW == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesNS / 2) * laneWidth;

				direction = 180.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				newX = xVehicleLocation + ((numberOfLanesEW == 2) ? 0.5 : 1.5) * laneWidth;
				newY = yVehicleLocation + (numberOfLanesNS / 2) * laneWidth;

				direction = 0.0;
			}
		}
	}

	// END HANDLING RARE EXCEPTION

	road->getSpeedLimitMPH();
	road->getSpeedLimitMPS();

	if (turnDecided == false)
	{
		// Decide turn at next intersection
		// set turnDecided to true
	}

	nextIntersection->intersectUpDate();

	
	// Because it's returning an enum I am not yet sure how to set this to a variable
	lightInst->getEWState();

	// Set vehicle speed
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

	// Get the center points of the next intersection
	double xCenter = nextIntersection->getxCenterPoint();
	double yCenter = nextIntersection->getyCenterPoint();

	if (direction == 0.0)
	{
		newX = xVehicleLocation + speedMPS;
		newY = yVehicleLocation;

		if (newX > xCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD - BD;

				newX = xCenter + BD;
				newY = yVehicleLocation - BC;

				direction = 90.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD + BD;

				newX = xCenter - BD;
				newY = yVehicleLocation + BC;

				direction = 270.0;
			}
		}


	}

	else if (direction == 90.0)
	{
		newX = xVehicleLocation + speedMPS;
		newY = yVehicleLocation;

		if (newX > xCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD - BD;

				newX = xCenter + BD;
				newY = yVehicleLocation - BC;

				direction = 90.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD + BD;

				newX = xCenter - BD;
				newY = yVehicleLocation + BC;

				direction = 270.0;
			}
		}


	}

	else if (direction == 180.0)
	{
		newX = xVehicleLocation + speedMPS;
		newY = yVehicleLocation;

		if (newX > xCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD - BD;

				newX = xCenter + BD;
				newY = yVehicleLocation - BC;

				direction = 90.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD + BD;

				newX = xCenter - BD;
				newY = yVehicleLocation + BC;

				direction = 270.0;
			}
		}


	}

	if (direction == 0.0)
	{
		newX = xVehicleLocation + speedMPS;
		newY = yVehicleLocation;

		if (newX > xCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD - BD;

				newX = xCenter + BD;
				newY = yVehicleLocation - BC;

				direction = 90.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD + BD;

				newX = xCenter - BD;
				newY = yVehicleLocation + BC;

				direction = 270.0;
			}
		}


	}
	
}

void Vehicle::PrintReport()
{

}

// Not a simple set function. Sets Vehicle speed after considering multiple factors in the environment
void Vehicle::updateVehicleSpeed(double mps, double mph, Road *roadInst, Intersection *intersectInst, TrafficLight *lightInst)
{
	// Meters
	double laneWidth = 36.6;
	double BC = ((roadInst->getLaneNumber()) == 4) ? (laneWidth * 2.0) : (laneWidth * 1.0);
	double AC = intersectInst->getxCenterPoint() - intersectInst->getyCenterPoint();
	double distNextIntersection = AC - BC;

	// Meters per second
	double speedLimitMPS = roadInst->getSpeedLimitMPS();

	// Miles per hour
	double speedLimitMPH = roadInst->getSpeedLimitMPH();
	double stopDist = 1.1 * speedMPH + 0.06 * pow(speedMPH, 2);

	// Because it's returning an enum I am not yet sure how to set this to a variable
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


