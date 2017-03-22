#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 


#include "Map.h"
#include "Intersection.h"

using namespace std;

Map::Map(char *filename)
{
	TrafficSimDataParser *dp = new TrafficSimDataParser(filename);

	for (int i = 0; i < dp->getRoadCount(); i++)
	{
		Road *road = new Road();

		char roadName[64];
		double xStart;
		double yStart;
		double xEnd;
		double yEnd;
		int intersectStart;
		int intersectEnd;
		double speedLimit;
		int numLanes;

		if (dp->getRoadData(roadName, &xStart, &yStart, &xEnd, &yEnd, &intersectStart, &intersectEnd, &speedLimit, &numLanes))
		{
			road->setRoadName(roadName);
			road->setxRoadStart(xStart);
			road->setyRoadStart(yStart);
			road->setxRoadEnd(xEnd);
			road->setyRoadEnd(yEnd);
			road->setStartIntersection(intersectStart);
			road->setEndIntersection(intersectEnd);
			road->setSpeedLimitMPH(speedLimit);
			road->setLaneNumber(numLanes);

			rCollect.push_back(road);
		}
	
	}

	// Collection of Intersections

	for (int i = 0; i < dp->getIntersectionCount(); i++)
	{
		Intersection *intersect = new Intersection();
		int ID;
		double xPosition;
		double yPosition;
		char nameN[32];
		char nameE[32];
		char nameS[32];
		char nameW[32];

		if (dp->getIntersectionData(&ID, &xPosition, &yPosition, nameN, nameE, nameS, nameW))
		{
			intersect->setIntersectionID(ID);
			intersect->setxCenterPoint(xPosition);
			intersect->setyCenterPoint(yPosition);
			intersect->setNameN(nameN);
			intersect->setNameE(nameE);
			intersect->setNameS(nameS);
			intersect->setNameW(nameW);

			iCollect.push_back(intersect);
		}
	}
}

Map::~Map()
{

}

Road * Map::getRoad(char * rdID)
{
	for (size_t i = 0; i < rCollect.size(); i++)
	{
		if (strcmp(rCollect[i]->getRoadName(), rdID) == 0)
		{
			return rCollect[i];
		}
	}

	Road *road = new Road();

	rCollect.push_back(road);

	return road;
}

Road * Map::getRoad(double x, double y, double dir)
{
	double XU;
	double YU;
	double XL;
	double YL;
	bool NSRoadFlag;

	for (size_t i = 0; i < rCollect.size(); i++)
	{
		if ((dir == 0.0) || (dir == 180.0))
		{
			XU = rCollect[i]->getxRoadStart();
			YU = rCollect[i]->getyRoadStart() - (rCollect[i]->getLaneNumber() / 2 * 3.6);
			XL = rCollect[i]->getxRoadEnd();
			YL = rCollect[i]->getyRoadEnd() + (rCollect[i]->getLaneNumber() / 2 * 3.6);
			NSRoadFlag = false;
		}

		else if ((dir == 90.0) || (dir == 270.0))
		{
			XU = rCollect[i]->getxRoadStart() - (rCollect[i]->getLaneNumber() / 2 * 3.6);
			YU = rCollect[i]->getyRoadStart();
			XL = rCollect[i]->getxRoadEnd() + (rCollect[i]->getLaneNumber() / 2 * 3.6);
			YL = rCollect[i]->getyRoadEnd();
			NSRoadFlag = true;
		}

		if ((x >= XU) && (x <= XL) && (y >= YU) && (y <= YL))
		{
			return rCollect[i];
		}
	}

	Road *road = new Road();

	rCollect.push_back(road);

	return road;
}

void Map::addIntersection(Intersection * i)
{
	iCollect.push_back(i);
}

Intersection * Map::getIntersection(int id)
{

	for (size_t i = 0; i < iCollect.size(); i++)
	{
		if (iCollect[i]->getIntersectionID() == id)
		{
			return  iCollect[i];
		}
	}

	Intersection *intersect = new Intersection();

	iCollect.push_back(intersect);

	return intersect;
}

Intersection * Map::getNextIntersection(double x, double y, double dir, char *roadName)
{
	bool checkIntersect;
	double minDist = 100000000000;
	double dist = 0;
	Intersection *nextInt = NULL;

	for (size_t i = 0; i < iCollect.size(); i++)
	{
		checkIntersect = false;

		if ((dir == 0.0) && (strcmp(iCollect[i]->getNameW(), roadName) == 0) && (x < iCollect[i]->getxCenterPoint()))
		{
			checkIntersect = true;
		}

		else if ((dir == 90.0) && (strcmp(iCollect[i]->getNameS(), roadName) == 0) && (y > iCollect[i]->getyCenterPoint()))
		{
			checkIntersect = true;
		}

		else if ((dir == 180.0) && (strcmp(iCollect[i]->getNameE(), roadName) == 0) && (x > iCollect[i]->getxCenterPoint()))
		{
			checkIntersect = true;
		}

		else if ((dir == 270.0) && (strcmp(iCollect[i]->getNameN(), roadName) == 0) && (y < iCollect[i]->getyCenterPoint()))
		{
			checkIntersect = true;
		}

		if (checkIntersect == true)
		{
			dist = sqrt(pow(x - iCollect[i]->getxCenterPoint(), 2.0) + pow(y - iCollect[i]->getyCenterPoint(), 2.0));

			if (dist < minDist)
			{
				minDist = dist;
				nextInt = iCollect[i];
				return nextInt;
			}
		}
	}

	return nextInt;
}

Intersection * Map::getIntersection(double x, double y)
{
	for (size_t i = 0; i < iCollect.size(); i++)
	{
		if ((iCollect[i]->getxIntersectCoord() == x) && (iCollect[i]->getyIntersectCoord() == y))
		{
			return iCollect[i];
		}
	}

	return nullptr;
}

void Map::PrintStatus()
{

}

void Map::upDate(double time)
{
	TrafficLight *light = new TrafficLight();
	for (size_t i = 0; i < iCollect.size(); i++)
	{
		iCollect[i]->intersectUpDate(light);
	}
}
