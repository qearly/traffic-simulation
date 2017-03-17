#include "includes.h"
#include "TrafficLight.h"
#include "Map.h"
#include "Road.h"

using namespace std;

Vehicle::Vehicle()
{

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

void Vehicle::Move()
{
	
	int intersectID = 0;
	TrafficSimDataParser *dp = new TrafficSimDataParser("TrafficSim01.xml");
	Map *mapInst = new Map(dp, roadName, &intersectID);
	road = mapInst->getRoad(roadName);
	Intersection *intersection = mapInst->getIntersection(intersectID);

// I am doing it this way because it makes sure the vehicle data 
// will not be reinitialized each time the move function is called
if (counter < 1)
{ 
	if(dp->getVehicleData(type, &carID, &xVehicleLocation, &yVehicleLocation, &direction, &Acceleration))
	{
		setType(type);
		setCarID(carID);
		setxVehicleLocation(xVehicleLocation);
		setyVehicleLocation(yVehicleLocation);
		setDirection(direction);
		setAcceleration(Acceleration);
	}

	counter++;
}
	// Adjusted x and y locations as the vehicle is moving

	double laneWidth = 3.6;
	double distToCenter = intersection->getxCenterPoint() - xVehicleLocation;
	double BD = ((road->getLaneNumber()) == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
	double distAfterTurn = speedMPS - distToCenter - BD;
	double newXIfTurn = intersection->getxCenterPoint() - distAfterTurn;
	double newYIfTurn = yVehicleLocation + distAfterTurn;
	double AD = 0;


	// FOR SETTING VEHICLE SPEED
	double BC = ((road->getLaneNumber()) == 4) ? (laneWidth * 2.0) : (laneWidth * 1.0);
	double AC = intersection->getxCenterPoint() - xVehicleLocation;
	double distNextIntersection = AC - BC;
	cout << "Distance to next intersection: " << distNextIntersection << endl;

	// END FOR SETTING VEHICLE SPEED

	bool turnDecided = false;

	// Some necessary objects
	Intersection *nextIntersection = new Intersection();
	Intersection *curIntersection = mapInst->getIntersection(intersectID);
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

				xVehicleLocation = xVehicleLocation + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yVehicleLocation + (numberOfLanesEW / 2) * laneWidth;

				
				direction = 90.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();

				xVehicleLocation = xVehicleLocation + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yVehicleLocation + (numberOfLanesEW / 2) * laneWidth;


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

				xVehicleLocation = xVehicleLocation + ((numberOfLanesEW == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yVehicleLocation + (numberOfLanesNS / 2) * laneWidth;

				direction = 0.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				xVehicleLocation = xVehicleLocation + ((numberOfLanesEW == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yVehicleLocation + (numberOfLanesNS / 2) * laneWidth;

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

				xVehicleLocation = xVehicleLocation + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yVehicleLocation + (numberOfLanesEW / 2) * laneWidth;

				direction = 270.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				xVehicleLocation = xVehicleLocation + ((numberOfLanesNS == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yVehicleLocation + (numberOfLanesEW / 2) * laneWidth;

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

				xVehicleLocation = xVehicleLocation + ((numberOfLanesEW == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yVehicleLocation + (numberOfLanesNS / 2) * laneWidth;

				direction = 180.0;
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numberOfLanesEW = tempRoad->getLaneNumber();
				tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numberOfLanesNS = tempRoad->getLaneNumber();

				xVehicleLocation = xVehicleLocation + ((numberOfLanesEW == 2) ? 0.5 : 1.5) * laneWidth;
				yVehicleLocation = yVehicleLocation + (numberOfLanesNS / 2) * laneWidth;

				direction = 0.0;
			}
		}
	}

	// END HANDLING RARE EXCEPTION

	if (turnDecided == false)
	{
		int rand_num = rand() % 100;

		if (rand_num < 30)
		{
			turnDirection = LEFT;
		}

		else if ((rand_num >= 30) && (rand_num <= 60))
		{
			turnDirection = RIGHT;
		}

		else if ((rand_num >= 60) && (rand_num <= 100))
		{
			turnDirection = STRAIGHT;
		}

		turnDecided = true;
	}

	double speedLimitMPH = road->getSpeedLimitMPH();
	double speedLimitMPS = speedLimitMPH * 0.44704;
	double stopDist = 1.1 * speedMPH + 0.06 * pow(speedMPH, 2);
	double stopDistSL = 1.1 * speedLimitMPH + 0.06 * pow(speedLimitMPH, 2);
	stopDistSL *= 0.3048;

	// Set vehicle speed
	if ((light->getNSState() == RED) || (light->getNSState() == YELLOW))
	{

		if (stopDistSL < distNextIntersection)
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

	// Get the center points of the next intersection
	double xCenter = nextIntersection->getxCenterPoint();
	double yCenter = nextIntersection->getyCenterPoint();

	if (direction == 0.0)
	{
		xVehicleLocation += speedMPS;
		yVehicleLocation = yVehicleLocation;

		if (xVehicleLocation > xCenter)
		{
			
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD - BD;

				xVehicleLocation = xCenter + BD;
				yVehicleLocation = yVehicleLocation - BC;

				setDirection(90.0);
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numLanes = tempRoad->getLaneNumber();

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


	}

	else if (direction == 90.0)
	{
		xVehicleLocation = xVehicleLocation + speedMPS;
		yVehicleLocation = yVehicleLocation;

		if (xVehicleLocation > xCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD - BD;

				xVehicleLocation = xCenter + BD;
				yVehicleLocation = yVehicleLocation - BC;

				setDirection(90.0);
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD + BD;

				xVehicleLocation = xCenter - BD;
				yVehicleLocation = yVehicleLocation + BC;

				setDirection(270.0);
			}
		}


	}

	else if (direction == 180.0)
	{
		xVehicleLocation = xVehicleLocation + speedMPS;
		yVehicleLocation = yVehicleLocation;

		if (xVehicleLocation > xCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameW());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD - BD;

				xVehicleLocation = xCenter + BD;
				yVehicleLocation = yVehicleLocation - BC;

				setDirection(90.0);
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameE());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD + BD;

				xVehicleLocation = xCenter - BD;
				yVehicleLocation = yVehicleLocation + BC;

				setDirection(270.0);
			}
		}


	}

	else if (direction == 270.0)
	{
		xVehicleLocation = xVehicleLocation + speedMPS;
		yVehicleLocation = yVehicleLocation;

		if (xVehicleLocation > xCenter)
		{
			if (turnDirection == LEFT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameS());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD - BD;

				xVehicleLocation = xCenter + BD;
				yVehicleLocation = yVehicleLocation - BC;

				setDirection(90.0);
			}

			else if (turnDirection == RIGHT)
			{
				tempRoad = mapInst->getRoad(curIntersection->getNameN());
				int numLanes = tempRoad->getLaneNumber();

				AC = speedMPS;
				BD = (numLanes == 4) ? (laneWidth * 1.5) : (laneWidth * .5);
				AD = xCenter - xVehicleLocation;
				BC = AC - AD + BD;

				xVehicleLocation = xCenter - BD;
				yVehicleLocation = yVehicleLocation + BC;

				setDirection(270.0);
			}
		}


	}
	
}

void Vehicle::PrintStatus()
{
	light->NSLightUpDate();
	light->EWLightUpDate();
	cout << "Vehicle type: " << type << endl;
	cout << "Vehicle X location: " << xVehicleLocation << endl;
	cout << "Vehicle Y location: " << yVehicleLocation << endl;
	cout << "Vehicle speed in MPH: " << speedMPH << endl;
	cout << "Road vehicle his driving on: " << road->getRoadName() << endl;


	if (direction == 0.0)
	{
		cout << "Vehicle direction: EAST" << endl;
	}

	else if (direction == 90.0)
	{
		cout << "Vehicle direction: NORTH" << endl;
	}

	else if (direction == 180.0)
	{
		cout << "Vehicle direction: WEST" << endl;
	}

	else if (direction == 270.0)
	{
		cout << "Vehicle direction: SOUTH" << endl;
	}

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

void Vehicle::setxVehicleLocation(double location)
{
	xVehicleLocation = location;
}

void Vehicle::setyVehicleLocation(double location)
{
	yVehicleLocation = location;
}

void Vehicle::setTurnDirection(turnState turnDirection)
{
	this->turnDirection = turnDirection;
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




// Testing new stuff

void Vehicle::Move()
{
	

// I am doing it this way because it makes sure the vehicle data 
// will not be reinitialized each time the move function is called
if (counter < 1)
{ 
	dp = new TrafficSimDataParser("TrafficSim01.xml");
	road = new Road();
	intersection = new Intersection();
	nextIntersection = new Intersection();
	if(dp->getVehicleData(type, &carID, &xVehicleLocation, &yVehicleLocation, &direction, &Acceleration))
	{
		setType(type);
		setCarID(carID);
		setxVehicleLocation(xVehicleLocation);
		setyVehicleLocation(yVehicleLocation);
		setDirection(direction);
		setAcceleration(Acceleration);
	}

	// Local variables needed to get the initial road and intersection
	char roadName[64];
	double xStart;
	double yStart;
	double xEnd;
	double yEnd;
	int intersectStart;
	int intersectEnd;
	double speedLimit;
	int numLanes;
	int intersectID;
	double xPosition;
	double yPosition;
	char nameN[32];
	char nameE[32];
	char nameS[32];
	char nameW[32];

	Map *map = new Map(dp);
	dp->getRoadData(roadName, &xStart, &yStart, &xEnd, &yEnd, &intersectStart, &intersectEnd, &speedLimit, &numLanes);
	dp->getIntersectionData(&intersectID, &xPosition, &yPosition, nameN, nameE, nameS, nameW);

	road->setRoadData(roadName, xStart, yStart, xEnd, yEnd, intersectStart, intersectEnd, speedLimit, numLanes);
	intersection->setIntersectionData(intersectID, xPosition, yPosition, nameN, nameE, nameS, nameW);

	road = map->getRoad(road->getRoadName());
	intersection = map->getIntersection(intersectID);

	counter++;
}
	// Adjusted x and y locations as the vehicle is moving

