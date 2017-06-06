/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: SixCylinderMovement.cpp
*   Author: Matt Stewart
*   Desc: Movement subclass
*   Date: 4-8-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/


#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 


#include "SixCylinderMovement.h"
#include "Vehicle.h"
#include "VehicleFactory.h"
#include "TrafficLightManager.h"
#include "Map.h"
#include "Road.h"
#include <stdlib.h>
#include <sys/types.h>    
#include <sys/timeb.h>     
#include <time.h>
#include <iomanip>

using namespace std;



void SixCylinderMovement::Move(char *filename)
{

	while (counter == 0)
	{

		counter = 1;
		max = 100;
		value = 0;
		turnDecided = false;
		light = new TrafficLightManager();
		road = new Road();
		intersection = new Intersection();
		nextIntersection = new Intersection();
		vehicle = new Vehicle();
		dp = TrafficSimDataParser::getInstance();
		dp->setDataFileName(filename);


		// Get instance of Map, which creates the collections of roads and intersections
		mapInst = new Map(filename);

		VehicleFactory *inst = new VehicleFactory();
		vehicle = inst->createVehicle("6-CYLINDER_CAR", filename);
		// Initalizing an instance of intersection 

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

		road = mapInst->getRoad("Avenue A");

		light->UpDate();

		counter++;
	} 

	// Adjusted x and y locations as the vehicle is moving
	srand((unsigned int)(time(NULL)));
	double xCenter;
	double yCenter;
	double laneWidth = 3.6;
	double distToCenter = intersection->getxCenterPoint() - vehicle->getxVehicleLocation();
	double BD = ((road->getLaneNumber()) == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
	double distAfterTurn = vehicle->getSpeedMPS() - distToCenter - BD;
	double AD = 0;

	// FOR SETTING VEHICLE SPEED
	double BC = ((road->getLaneNumber()) == 4) ? (laneWidth * 2.0) : (laneWidth * 1.0);
	double AC = intersection->getxCenterPoint() - vehicle->getxVehicleLocation();
	double distNextIntersection = AC - BC;

	// END FOR SETTING VEHICLE SPEED

	// Will be necessary later
	Road *tempRoad = new Road();

	if (road == NULL)
	{
		double tempLocation = 0;

		if (vehicle->getDirection() == 0.0)
		{
			tempLocation = vehicle->getxVehicleLocation() + laneWidth * 2.0;
			vehicle->setxVehicleLocation(tempLocation);
		}

		else if (vehicle->getDirection() == 90.0)
		{
			tempLocation = vehicle->getyVehicleLocation() - laneWidth * 2.0;
			vehicle->setyVehicleLocation(tempLocation);
		}

		else if (vehicle->getDirection() == 180.0)
		{
			tempLocation = vehicle->getxVehicleLocation() - laneWidth * 2.0;
			vehicle->setxVehicleLocation(tempLocation);
		}

		else if (vehicle->getDirection() == 270.0)
		{
			tempLocation = vehicle->getyVehicleLocation() + laneWidth * 2.0;
			vehicle->setyVehicleLocation(tempLocation);
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

	nextIntersection = mapInst->getNextIntersection(vehicle->getxVehicleLocation(), vehicle->getyVehicleLocation(), vehicle->getDirection(), road->getRoadName());

	// HANDLING RARE EXCEPTION 
	if (nextIntersection == NULL)
	{
		Intersection *tempInt = new Intersection;
		tempInt = mapInst->getIntersection(intersection->getIntersectionID());

		xCenter = tempInt->getxCenterPoint();
		yCenter = tempInt->getyCenterPoint();

		if (vehicle->getDirection() == 0.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();

				vehicle->setxVehicleLocation(xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth);
				vehicle->setyVehicleLocation(yCenter + (numberOfLanesEW / 2) * laneWidth);


				vehicle->setDirection(90.0);
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();

				vehicle->setxVehicleLocation(xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth);
				vehicle->setyVehicleLocation(yCenter + (numberOfLanesEW / 2) * laneWidth);


				vehicle->setDirection(270.0);
			}
		}

		else if (vehicle->getDirection() == 90.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				vehicle->setxVehicleLocation(xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth);
				vehicle->setyVehicleLocation(yCenter + (numberOfLanesEW / 2) * laneWidth);


				vehicle->setDirection(180.0);
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				vehicle->setxVehicleLocation(xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth);
				vehicle->setyVehicleLocation(yCenter + (numberOfLanesEW / 2) * laneWidth);

				vehicle->setDirection(0.0);
			}
		}

		else if (vehicle->getDirection() == 180.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				vehicle->setxVehicleLocation(xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth);
				vehicle->setyVehicleLocation(yCenter + (numberOfLanesEW / 2) * laneWidth);

				vehicle->setDirection(270.0);
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				vehicle->setxVehicleLocation(xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth);
				vehicle->setyVehicleLocation(yCenter + (numberOfLanesEW / 2) * laneWidth);

				vehicle->setDirection(90.0);
			}
		}

		else if (vehicle->getDirection() == 270.0)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				vehicle->setxVehicleLocation(xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth);
				vehicle->setyVehicleLocation(yCenter + (numberOfLanesEW / 2) * laneWidth);

				vehicle->setDirection(180.0);
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				vehicle->setxVehicleLocation(xCenter + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth);
				vehicle->setyVehicleLocation(yCenter + (numberOfLanesEW / 2) * laneWidth);

				vehicle->setDirection(0.0);
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
	double stopDist = 1.1 * vehicle->getSpeedMPH() + 0.06 * pow(vehicle->getSpeedMPH(), 2);
	double stopDistSL = 1.1 * speedLimitMPH + 0.06 * pow(speedLimitMPH, 2);
	stopDistSL *= 0.3048;



	// Set vehicle speed

	// If going North or South
	if ((vehicle->getDirection() == 90.0) || (vehicle->getDirection() == 270.0))
	{
		double speedMPS = vehicle->getSpeedMPS();
		double speedMPH = vehicle->getSpeedMPH();

		if ((light->getNSState() == RED) || (light->getNSState() == YELLOW))
		{

			if (stopDistSL < distNextIntersection)
			{

				if (vehicle->getSpeedMPS() < speedLimitMPS)
				{

					speedMPS += vehicle->getAcceleration();
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
					speedMPS -= vehicle->getAcceleration();
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
				speedMPS += vehicle->getAcceleration();
				speedMPH = speedMPS / 0.44704;

				if (speedMPS > speedLimitMPS)
				{
					speedMPS = speedLimitMPS;
					speedMPH = speedMPS / 0.44704;
				}
			}

		}

		vehicle->setSpeedMPS(speedMPS);
		vehicle->setSpeedMPH(speedMPH);

	}

	// If going East or West
	if ((vehicle->getDirection() == 0.0) || (vehicle->getDirection() == 180.0))
	{
		double speedMPS = vehicle->getSpeedMPS();
		double speedMPH = vehicle->getSpeedMPH();

		if ((light->getEWState() == RED) || (light->getEWState() == YELLOW))
		{

			if (stopDistSL < distNextIntersection)
			{

				if (speedMPS < speedLimitMPS)
				{
					speedMPS += vehicle->getAcceleration();
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
					speedMPS -= vehicle->getAcceleration();
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
				speedMPS += vehicle->getAcceleration();
				speedMPH = speedMPS / 0.44704;

				if (speedMPS > speedLimitMPS)
				{
					speedMPS = speedLimitMPS;
					speedMPH = speedMPS / 0.44704;
				}
			}

		}

		vehicle->setSpeedMPS(speedMPS);
		vehicle->setSpeedMPH(speedMPH);
	}

	// Get the center points of the next intersection
	xCenter = nextIntersection->getxCenterPoint();
	yCenter = nextIntersection->getyCenterPoint();

	if (vehicle->getDirection() == 0.0)
	{
		vehicle->setxVehicleLocation(vehicle->getxVehicleLocation() + vehicle->getSpeedMPS());
		vehicle->setyVehicleLocation(vehicle->getyVehicleLocation());

		if (vehicle->getxVehicleLocation() > xCenter)
		{

			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numLanes = tempRoad->getLaneNumber();

				// In other words, if the road we want to turn left on is null
				if (numLanes == 0)
				{
	
						tempRoad = mapInst->getRoad(intersection->getNameS());
						numLanes = tempRoad->getLaneNumber();

						AC = vehicle->getSpeedMPS();
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = xCenter - vehicle->getxVehicleLocation();
						BC = AC - AD + BD;

						vehicle->setxVehicleLocation(xCenter - BD);
						vehicle->setyVehicleLocation(vehicle->getyVehicleLocation() + BC);

						road = mapInst->getRoad(intersection->getNameS());

						vehicle->setDirection(270.0);

				}

				else if (numLanes != 0)
				{
					AC = vehicle->getSpeedMPS();
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = xCenter - vehicle->getxVehicleLocation();
					BC = AC - AD - BD;

					vehicle->setxVehicleLocation(xCenter + BD);
					vehicle->setyVehicleLocation(vehicle->getyVehicleLocation() - BC);

					road = mapInst->getRoad(intersection->getNameN());
					vehicle->setDirection(90.0);
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

						tempRoad = mapInst->getRoad(intersection->getNameN());
						numLanes = tempRoad->getLaneNumber();

						AC = vehicle->getSpeedMPS();
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = xCenter - vehicle->getxVehicleLocation();
						BC = AC - AD - BD;

						vehicle->setxVehicleLocation(xCenter + BD);
						vehicle->setyVehicleLocation(vehicle->getyVehicleLocation() - BC);

						road = mapInst->getRoad(intersection->getNameN());
						vehicle->setDirection(90.0);
				}

				else if (numLanes != 0)
				{
					AC = vehicle->getSpeedMPS();
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = xCenter - vehicle->getxVehicleLocation();
					BC = AC - AD + BD;

					vehicle->setxVehicleLocation(xCenter - BD);
					vehicle->setyVehicleLocation(vehicle->getyVehicleLocation() + BC);

					road = mapInst->getRoad(intersection->getNameS());

					vehicle->setDirection(270.0);
				}

			}

			turnDecided = false;
		}

	}

	else if (vehicle->getDirection() == 90.0)
	{
		vehicle->setxVehicleLocation(vehicle->getxVehicleLocation());
		vehicle->setyVehicleLocation(vehicle->getyVehicleLocation() - vehicle->getSpeedMPS());

		if (vehicle->getyVehicleLocation() < yCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameW());
				int numLanes = tempRoad->getLaneNumber();

				// Again, same as above
				if (numLanes == 0)
				{
						tempRoad = mapInst->getRoad(intersection->getNameE());
						numLanes = tempRoad->getLaneNumber();

						AC = vehicle->getSpeedMPS();
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = yCenter - vehicle->getyVehicleLocation();
						BC = AC - AD + BD;

						vehicle->setxVehicleLocation(vehicle->getxVehicleLocation() + BC);
						vehicle->setyVehicleLocation(yCenter - BD);

						road = mapInst->getRoad(intersection->getNameE());
						vehicle->setDirection(0.0);

				}

				else if (numLanes != 0)
				{
					AC = vehicle->getSpeedMPS();
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = yCenter - vehicle->getyVehicleLocation();
					BC = AC - AD - BD;

					vehicle->setxVehicleLocation(vehicle->getxVehicleLocation() - BC);
					vehicle->setyVehicleLocation(yCenter + BD);

					road = mapInst->getRoad(intersection->getNameW());

					vehicle->setDirection(180.0);
				}
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameE());
				int numLanes = tempRoad->getLaneNumber();

				if (numLanes == 0)
				{
					
						tempRoad = mapInst->getRoad(intersection->getNameW());
						numLanes = tempRoad->getLaneNumber();

						AC = vehicle->getSpeedMPS();
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = yCenter - vehicle->getyVehicleLocation();
						BC = AC - AD - BD;

						vehicle->setxVehicleLocation(vehicle->getxVehicleLocation() - BC);
						vehicle->setyVehicleLocation(yCenter + BD);

						road = mapInst->getRoad(intersection->getNameW());

						vehicle->setDirection(180.0);
					

				}

				else if (numLanes != 0)
				{
					AC = vehicle->getSpeedMPS();
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = yCenter - vehicle->getyVehicleLocation();
					BC = AC - AD + BD;

					vehicle->setxVehicleLocation(vehicle->getxVehicleLocation() + BC);
					vehicle->setyVehicleLocation(yCenter - BD);

					road = mapInst->getRoad(intersection->getNameE());
					vehicle->setDirection(0.0);
				}

			}

			turnDecided = false;
		}


	}

	else if (vehicle->getDirection() == 180.0)
	{
		vehicle->setxVehicleLocation(vehicle->getxVehicleLocation() - vehicle->getSpeedMPS());
		vehicle->setyVehicleLocation(vehicle->getyVehicleLocation());

		if (vehicle->getxVehicleLocation() < xCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameS());
				int numLanes = tempRoad->getLaneNumber();

				if (numLanes == 0)
				{
					
						tempRoad = mapInst->getRoad(intersection->getNameN());

						numLanes = tempRoad->getLaneNumber();

						AC = vehicle->getSpeedMPS();
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = xCenter + vehicle->getxVehicleLocation();
						BC = AC - AD - BD;

						vehicle->setxVehicleLocation(xCenter + BD);
						vehicle->setyVehicleLocation(vehicle->getyVehicleLocation() - BC);

						road = mapInst->getRoad(intersection->getNameN());
						vehicle->setDirection(90.0);
					

				}

				else if (numLanes != 0)
				{
					AC = vehicle->getSpeedMPS();
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = xCenter - vehicle->getxVehicleLocation();
					BC = AC - AD + BD;

					vehicle->setxVehicleLocation(xCenter - BD);
					vehicle->setyVehicleLocation(vehicle->getyVehicleLocation() + BC);

					road = mapInst->getRoad(intersection->getNameS());
					vehicle->setDirection(270.0);
				}

			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(intersection->getNameN());
				int numLanes = tempRoad->getLaneNumber();

				if (numLanes == 0)
				{
					
						tempRoad = mapInst->getRoad(intersection->getNameS());
						numLanes = tempRoad->getLaneNumber();

						AC = vehicle->getSpeedMPS();
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = xCenter - vehicle->getxVehicleLocation();
						BC = AC - AD - BD;

						vehicle->setxVehicleLocation(xCenter - BD);
						vehicle->setyVehicleLocation(vehicle->getyVehicleLocation() + BC);

						road = mapInst->getRoad(intersection->getNameS());
						vehicle->setDirection(270.0);
					
				}

				else if (numLanes != 0)
				{
					AC = vehicle->getSpeedMPS();
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = xCenter - vehicle->getxVehicleLocation();
					BC = AC - AD + BD;

					vehicle->setxVehicleLocation(xCenter + BD);
					vehicle->setyVehicleLocation(vehicle->getyVehicleLocation() - BC);

					road = mapInst->getRoad(intersection->getNameN());
					vehicle->setDirection(90.0);
				}

			}

			turnDecided = false;
		}


	}

	else if (vehicle->getDirection() == 270.0)
	{
		vehicle->setxVehicleLocation(vehicle->getxVehicleLocation());
		vehicle->setyVehicleLocation(vehicle->getyVehicleLocation() + vehicle->getSpeedMPS());

		if (vehicle->getyVehicleLocation() > yCenter)
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

						AC = vehicle->getSpeedMPS();
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = yCenter - vehicle->getyVehicleLocation();
						BC = AC - AD + BD;

						vehicle->setxVehicleLocation(vehicle->getxVehicleLocation() - BC);
						vehicle->setyVehicleLocation(yCenter + BD);

						road = mapInst->getRoad(intersection->getNameW());
						vehicle->setDirection(180.0);
					}

				}

				else if (numLanes != 0)
				{
					AC = vehicle->getSpeedMPS();
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = yCenter - vehicle->getyVehicleLocation();
					BC = AC - AD - BD;

					vehicle->setxVehicleLocation(vehicle->getxVehicleLocation() + BC);
					vehicle->setyVehicleLocation(yCenter - BD);

					road = mapInst->getRoad(intersection->getNameE());
					vehicle->setDirection(0.0);
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

						AC = vehicle->getSpeedMPS();
						BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
						AD = yCenter - vehicle->getyVehicleLocation();
						BC = AC - AD - BD;

						vehicle->setxVehicleLocation(vehicle->getxVehicleLocation() + BC);
						vehicle->setyVehicleLocation(yCenter - BD);

						road = mapInst->getRoad(intersection->getNameE());
						vehicle->setDirection(0.0);
					}

				}

				else if (numLanes != 0)
				{
					AC = vehicle->getSpeedMPS();
					BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
					AD = yCenter - vehicle->getyVehicleLocation();
					BC = AC - AD + BD;

					vehicle->setxVehicleLocation(vehicle->getxVehicleLocation() - BC);
					vehicle->setyVehicleLocation(yCenter + BD);

					road = mapInst->getRoad(intersection->getNameW());
					vehicle->setDirection(180.0);
				}
			}

			turnDecided = false;
		}


	}

	// Update the status of traffic lights at each intersection
	light->UpDate();

	intersection = nextIntersection;
}

void SixCylinderMovement::PrintStatus()
{
	cout << "Vehicle type: " << vehicle->getType() << endl;
	cout << "Vehicle is currently traveling along " << road->getRoadName() << "," << " driving at " << vehicle->getDirection() << " degrees, going a speed of " << vehicle->getSpeedMPH() << " MPH." << endl;
	cout << "The current location of Vehicle is at these X/Y coordinates: (" << vehicle->getxVehicleLocation() << ", " << vehicle->getyVehicleLocation() << ")" << endl;

	cout << endl;
}
