#include "Map.h"

using namespace std;


Map::Map(TrafficSimDataParser *dp)
{
	// Collection of Roads
	int rCount = dp->getRoadCount();
	char roadName[64];
	double xStart;
	double yStart;
	double xEnd;
	double yEnd;
	int intersectStart;
	int intersectEnd;
	double speedLimit;
	int numLanes;

	for (int i = 0; i <= rCount; i++)
	{ 
		dp->getRoadData(roadName, &xStart, &yStart, &xEnd, &yEnd, &intersectStart, &intersectEnd, &speedLimit, &numLanes);
	}

	// Collection of Intersections
	int iCount = dp->getIntersectionCount();
	int ID;
	double xPosition;
	double yPosition;
	char nameN[32];
	char nameE[32];
	char nameS[32];
	char nameW[32];

	for (int j = 0; j <= iCount; j++)
	{
		dp->getIntersectionData(&ID, &xPosition, &yPosition, nameN, nameE, nameS, nameW);
	}
}

Map::~Map()
{

}

Road * Map::getRoad(char * rdID)
{
	for (int i = 0; i < rCollect.size(); i++)
	{
		if (strcmp(rCollect[i]->getRoadName(), rdID) == 0)
		{
			return rCollect[i];
		}
	}

	return nullptr;
}

Road * Map::getRoad(double x, double y, double dir)
{
	for (int i = 0; i < rCollect.size(); i++)
	{
		if ((rCollect[i]->getxCoord() == x) && (rCollect[i]->getyCoord() == y) && ((rCollect[i]->getDirectionNS() == dir) || rCollect[i]->getDirectionEW() == dir))
		{
			return rCollect[i];
		}
	}

	return nullptr;
}

void Map::addIntersection(Intersection * i)
{
	iCollect.push_back(i);
}

Intersection * Map::getIntersection(int id)
{
	for (int i = 0; i < iCollect.size(); i++)
	{
		if (iCollect[i]->getIntersectionID == id)
		{
			return  iCollect[i];
		}
	}

	return nullptr;
}

Intersection * Map::getNextIntersection(double x, double y, double dir)
{
	Intersection *nextInt = new Intersection();
	bool checkIntersect;
	double minDist = 65536.999;
	double dist = 0;
	nextInt = NULL;

	for (int i = 0; i < iCollect.size(); i++)
	{
		checkIntersect = false;

		if ((dir == 0.0) && (iCollect[i]->getNameW == iCollect[i]->getCurRoad) && (x < iCollect[i]->getxCenterPoint))
		{
			checkIntersect = true;
		}

		else if ((dir == 90.0) && (iCollect[i]->getNameS == iCollect[i]->getCurRoad) && (y > iCollect[i]->getyCenterPoint))
		{
			checkIntersect = true;
		}

		else if ((dir == 180.0) && (iCollect[i]->getNameE == iCollect[i]->getCurRoad) && (x > iCollect[i]->getxCenterPoint))
		{
			checkIntersect = true;
		}

		else if ((dir == 270.0) && (iCollect[i]->getNameN == iCollect[i]->getCurRoad) && (y < iCollect[i]->getyCenterPoint))
		{
			checkIntersect = true;
		}

		if (checkIntersect = true)
		{
			dist = sqrt(pow(x - iCollect[i]->getxCenterPoint, 2.0) + pow(y - iCollect[i]->getyCenterPoint, 2.0));

			if (dist < minDist)
			{
				minDist = dist;
				nextInt = iCollect[i];
			}
		}
	}

	return nextInt;
}

Intersection * Map::getIntersection(double x, double y)
{
	for (int i = 0; i < iCollect.size(); i++)
	{
		if ((iCollect[i]->getxIntersectCoord() == x) && (iCollect[i]->getyIntersectCoord() == y))
		{
			return iCollect[i];
		}
	}

	return nullptr;
}

void Map::PrintReport()
{

}

void Map::upDate(double time)
{
	for (int i = 0; i < iCollect.size(); i++)
	{
		iCollect[i]->intersectUpDate();
	}
}
