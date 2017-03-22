#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 


#include "includes.h"
#include "TrafficLight.h"
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
}

Vehicle::~Vehicle()
{

}

void Vehicle::Move(char *filename)
{
	
	// I am doing it this way because it makes sure the vehicle data 
	// and other data will not be reinitialized each time the move function is called
	if (counter < 1)
	{
		dp = new TrafficSimDataParser(filename);

		// Get instance of Map, which creates the collections of roads and intersections
		mapInst = new Map(filename);

		// Get the vehicle data. There's only one vehicle so this can be done just once.
		if (dp->getVehicleData(type, &carID, &xVehicleLocation, &yVehicleLocation, &direction, &Acceleration))
		{
			setType(type);
			setCarID(carID);
			setxVehicleLocation(xVehicleLocation);
			setyVehicleLocation(yVehicleLocation);
			setDirection(direction);
			setAcceleration(Acceleration);
		}

		// Initalizing an instance of intersection and road. 

		int intersectionID;
		double xPosition;
		double yPosition;
		char nameN[32];
		char nameE[32];
		char nameS[32];
		char nameW[32];

		if (dp->getIntersectionData(&intersectionID, &xPosition, &yPosition, nameN, nameE, nameS, nameW))
		{ 
			intersection->setIntersectionID(intersectionID);
			intersection->setxCenterPoint(xPosition);
			intersection->setyCenterPoint(yPosition);
			intersection->setNameN(nameN);
			intersection->setNameE(nameE);
			intersection->setNameS(nameS);
			intersection->setNameW(nameW);
		}

		char name[64];
		double xStart;
		double yStart;
		double xEnd;
		double yEnd;
		int intersectStart;
		int intersectEnd;
		double speedLimit;
		int numLanes;

		if (dp->getRoadData(name, &xStart, &yStart, &xEnd, &yEnd, &intersectStart, &intersectEnd, &speedLimit, &numLanes))
		{
			road->setRoadData(name, xStart, yStart, xEnd, yEnd, intersectStart, intersectEnd, speedLimit, numLanes);
		}

		intersection->intersectUpDate(light);

		srand((unsigned int)(time(NULL)));
		counter++;
	}

	// Adjusted x and y locations as the vehicle is moving

	double xCenter;
	double yCenter;
	double laneWidth = 3.6;
	double distToCenter = intersection->getxCenterPoint() - xVehicleLocation;
	double BD = ((road->getLaneNumber()) == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
	double distAfterTurn = speedMPS - distToCenter - BD;
	double AD = 0;

	// FOR SETTING VEHICLE SPEED
	double BC = ((road->getLaneNumber()) == 4) ? (laneWidth * 2.0) : (laneWidth * 1.0);
	double AC = intersection->getxCenterPoint() - xVehicleLocation;
	double distNextIntersection = AC - BC;

	// END FOR SETTING VEHICLE SPEED

	// Will be necessary later
	Road *tempRoad = new Road();

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
		}

	}

	nextIntersection = mapInst->getNextIntersection(xVehicleLocation, yVehicleLocation, direction, road->getRoadName());
	
	// HANDLING RARE EXCEPTION 
	if (nextIntersection == NULL)
	{
		Intersection *tempInt = new Intersection;
		tempInt = mapInst->getIntersection(intersection->getIntersectionID());

		xCenter = tempInt->getxCenterPoint();
		yCenter = tempInt->getyCenterPoint();

		if (direction == 0.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();
	
				xVehicleLocation = xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yCenter + (numberOfLanesEW / 2) * laneWidth;

				
				direction = 90.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();

				xVehicleLocation = xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yCenter + (numberOfLanesEW / 2) * laneWidth;


				direction = 270.0;
			}
		}

		else if (direction == 90.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				xVehicleLocation = xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yCenter + (numberOfLanesEW / 2) * laneWidth;

				direction = 180.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				xVehicleLocation = xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yCenter + (numberOfLanesEW / 2) * laneWidth;

				direction = 0.0;
			}
		}

		else if (direction == 180.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				xVehicleLocation = xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yCenter + (numberOfLanesEW / 2) * laneWidth;

				direction = 270.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				xVehicleLocation = xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yCenter + (numberOfLanesEW / 2) * laneWidth;

				direction = 90.0;
			}
		}

		else if (direction == 270.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				xVehicleLocation = xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yCenter + (numberOfLanesEW / 2) * laneWidth;

				direction = 180.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				xVehicleLocation = xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yCenter + (numberOfLanesEW / 2) * laneWidth;

				direction = 0.0;
			}
		}

		nextIntersection = mapInst->getIntersection(intersection->getIntersectionID());
	}

	// END HANDLING RARE EXCEPTION


	if (turnDecided == false)
	{
		value = rand() % max;

		if (value < 30)
		{
			turnDirection = LEFT;

			turnDecided = true;
		}

		else if ((value >= 30) && (value <= 60))
		{
			turnDirection = RIGHT;

			turnDecided = true;
		}

		else if ((value >= 60) && (value <= 100))
		{
			turnDirection = STRAIGHT;
			turnDecided = false;
		}
	}

	// Setting the speed limit and stop distances
	double speedLimitMPH = road->getSpeedLimitMPH();
	double speedLimitMPS = speedLimitMPH * 0.44704;
	double stopDist = 1.1 * speedMPH + 0.06 * pow(speedMPH, 2);
	double stopDistSL = 1.1 * speedLimitMPH + 0.06 * pow(speedLimitMPH, 2);
	stopDistSL *= 0.3048;



	// Set vehicle speed

	// If going North or South
	if ((direction == 90.0) || (direction == 270.0))
	{
		if ((light->getNSState() == RED) || (light->getNSState() == YELLOW))
		{

			if (stopDistSL < distNextIntersection)
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

			else if ((stopDistSL > distNextIntersection) && (speedMPS != 0))
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
					stopDist = 1.1 * speedMPH + 0.06 * pow(speedMPH, 2);
					stopDist *= 0.3048;
					if (speedMPS == 0)
					{
						break;
					}
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

	}

	// If going East or West
	if ((direction == 0.0) || (direction == 180.0))
	{
		if ((light->getEWState() == RED) || (light->getEWState() == YELLOW))
		{

			if (stopDistSL < distNextIntersection)
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
					stopDist = 1.1 * speedMPH + 0.06 * pow(speedMPH, 2);
					stopDist *= 0.3048;
					if (speedMPS == 0)
					{
						break;
					}
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
	}
	
	// Get the center points of the next intersection
	xCenter = nextIntersection->getxCenterPoint();
    yCenter = nextIntersection->getyCenterPoint();

	if (direction == 0.0)
	{
		xVehicleLocation = xVehicleLocation + speedMPS;
		yVehicleLocation = yVehicleLocation;

		if (xVehicleLocation > xCenter)
		{
			
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numLanes = tempRoad->getLaneNumber();

				// In other words, if the road we want to turn left on is null
				if (numLanes == 0)
				{
					// Now we are going to decide between turning right and continuing straight.
					value = rand() % max;

					// 40% of the time we will turn right, else we will continue going straight
					if (value <= 40)
					{
						tempRoad = mapInst->getRoad(intersection->getNameS());
						numLanes = tempRoad->getLaneNumber();

						AC = speedMPS;
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = xCenter - xVehicleLocation;
						BC = AC - AD + BD;

						xVehicleLocation = xCenter - BD;
						yVehicleLocation = yVehicleLocation + BC;

						road = mapInst->getRoad(intersection->getNameS());

						setDirection(270.0);
					}

				}

				else if (numLanes != 0)
				{
					AC = speedMPS;
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = xCenter - xVehicleLocation;
					BC = AC - AD - BD;

					xVehicleLocation = xCenter + BD;
					yVehicleLocation = yVehicleLocation - BC;

					road = mapInst->getRoad(intersection->getNameN());
					setDirection(90.0);
				}
		
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numLanes = tempRoad->getLaneNumber();

				// Same as above
				if (numLanes == 0)
				{
					value = rand() % max;

					if (value <= 40)
					{
						tempRoad = mapInst->getRoad(intersection->getNameN());
						numLanes = tempRoad->getLaneNumber();

						AC = speedMPS;
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = xCenter - xVehicleLocation;
						BC = AC - AD - BD;

						xVehicleLocation = xCenter + BD;
						yVehicleLocation = yVehicleLocation - BC;

						road = mapInst->getRoad(intersection->getNameN());
						setDirection(90.0);
					}
				}

				else if (numLanes != 0)
				{
					AC = speedMPS;
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = xCenter - xVehicleLocation;
					BC = AC - AD + BD;

					xVehicleLocation = xCenter - BD;
					yVehicleLocation = yVehicleLocation + BC;

					road = mapInst->getRoad(intersection->getNameS());

					setDirection(270.0);
				}

			}

			turnDecided = false;
		}

	}

	else if (direction == 90.0)
	{
		xVehicleLocation = xVehicleLocation;
		yVehicleLocation = yVehicleLocation - speedMPS;

		if (yVehicleLocation < yCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numLanes = tempRoad->getLaneNumber();

				// Again, same as above
				if (numLanes == 0)
				{
					value = rand() % max;
					if (value <= 40)
					{
						tempRoad = mapInst->getRoad(intersection->getNameE());
						numLanes = tempRoad->getLaneNumber();

						AC = speedMPS;
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = yCenter - yVehicleLocation;
						BC = AC - AD + BD;

						xVehicleLocation = xVehicleLocation + BC;
						yVehicleLocation = yCenter - BD;

						road = mapInst->getRoad(intersection->getNameE());
						setDirection(0.0);
					}
	
				}

				else if (numLanes != 0)
				{
					AC = speedMPS;
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = yCenter - yVehicleLocation;
					BC = AC - AD - BD;

					xVehicleLocation = xVehicleLocation - BC;
					yVehicleLocation = yCenter + BD;

					road = mapInst->getRoad(intersection->getNameW());

					setDirection(180.0);
				}
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numLanes = tempRoad->getLaneNumber();

				if (numLanes == 0)
				{
					value = rand() % max;

					if (value <= 40)
					{
						tempRoad = mapInst->getRoad(intersection->getNameW());
						numLanes = tempRoad->getLaneNumber();

						AC = speedMPS;
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = yCenter - yVehicleLocation;
						BC = AC - AD - BD;

						xVehicleLocation = xVehicleLocation - BC;
						yVehicleLocation = yCenter + BD;

						road = mapInst->getRoad(intersection->getNameW());

						setDirection(180.0);
					}
	
				}

				else if (numLanes != 0)
				{
					AC = speedMPS;
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = yCenter - yVehicleLocation;
					BC = AC - AD + BD;

					xVehicleLocation = xVehicleLocation + BC;
					yVehicleLocation = yCenter - BD;

					road = mapInst->getRoad(intersection->getNameE());
					setDirection(0.0);
				}

			}

			turnDecided = false;
		}


	}

	else if (direction == 180.0)
	{
		xVehicleLocation = xVehicleLocation - speedMPS;
		yVehicleLocation = yVehicleLocation;

		if (xVehicleLocation < xCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numLanes = tempRoad->getLaneNumber();

				if (numLanes == 0)
				{
					value = rand() % max;

					if (value <= 40)
					{
						tempRoad = mapInst->getRoad(intersection->getNameN());

						numLanes = tempRoad->getLaneNumber();

						AC = speedMPS;
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = xCenter - xVehicleLocation;
						BC = AC - AD + BD;

						xVehicleLocation = xCenter - BD;
						yVehicleLocation = yVehicleLocation + BC;

						road = mapInst->getRoad(intersection->getNameN());
						setDirection(90.0);
					}

				}

				else if (numLanes != 0)
				{
					AC = speedMPS;
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = xCenter - xVehicleLocation;
					BC = AC - AD - BD;

					xVehicleLocation = xCenter + BD;
					yVehicleLocation = yVehicleLocation - BC;

					road = mapInst->getRoad(intersection->getNameS());
					setDirection(270.0);
				}

			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numLanes = tempRoad->getLaneNumber();

				if (numLanes == 0)
				{
					value = rand() % max;
					if (value <= 40)
					{
						tempRoad = mapInst->getRoad(intersection->getNameS());
						numLanes = tempRoad->getLaneNumber();

						AC = speedMPS;
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = xCenter - xVehicleLocation;
						BC = AC - AD - BD;

						xVehicleLocation = xCenter + BD;
						yVehicleLocation = yVehicleLocation - BC;

						road = mapInst->getRoad(intersection->getNameS());
						setDirection(270.0);
					}
				}

				else if (numLanes != 0)
				{
					AC = speedMPS;
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = xCenter - xVehicleLocation;
					BC = AC - AD + BD;

					xVehicleLocation = xCenter - BD;
					yVehicleLocation = yVehicleLocation + BC;

					road = mapInst->getRoad(intersection->getNameN());
					setDirection(90.0);
				}
		
			}

			turnDecided = false;
		}


	}

	else if (direction == 270.0)
	{
		xVehicleLocation = xVehicleLocation;
		yVehicleLocation = yVehicleLocation + speedMPS;

		if (yVehicleLocation > yCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numLanes = tempRoad->getLaneNumber();

				if (numLanes == 0)
				{
					value = rand() % max;
					if (value <= 40)
					{
						tempRoad = mapInst->getRoad(intersection->getNameW());
						numLanes = tempRoad->getLaneNumber();

						AC = speedMPS;
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = yCenter - yVehicleLocation;
						BC = AC - AD + BD;

						xVehicleLocation = xVehicleLocation - BC;
						yVehicleLocation = yCenter + BD;

						road = mapInst->getRoad(intersection->getNameW());
						setDirection(180.0);
					}
	
				}

				else if (numLanes != 0)
				{
					AC = speedMPS;
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = yCenter - yVehicleLocation;
					BC = AC - AD - BD;

					xVehicleLocation = xVehicleLocation + BC;
					yVehicleLocation = yCenter - BD;

					road = mapInst->getRoad(intersection->getNameE());
					setDirection(0.0);
				}
		
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numLanes = tempRoad->getLaneNumber();

				if (numLanes == 0)
				{
					value = rand() % max;

					if (value <= 40)
					{
						tempRoad = mapInst->getRoad(intersection->getNameE());
						numLanes = tempRoad->getLaneNumber();

						AC = speedMPS;
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = yCenter - yVehicleLocation;
						BC = AC - AD - BD;

						xVehicleLocation = xVehicleLocation + BC;
						yVehicleLocation = yCenter - BD;

						road = mapInst->getRoad(intersection->getNameE());
						setDirection(0.0);
					}
			
				}

				else if (numLanes != 0)
				{
					AC = speedMPS;
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = yCenter - yVehicleLocation;
					BC = AC - AD + BD;

					xVehicleLocation = xVehicleLocation - BC;
					yVehicleLocation = yCenter + BD;

					road = mapInst->getRoad(intersection->getNameW());
					setDirection(180.0);
				}
			}

			turnDecided = false;
		}


	}
	
	// Update the status of traffic lights at each intersection
	intersection->intersectUpDate(light);

	intersection = nextIntersection;
}

void Vehicle::PrintStatus()
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
