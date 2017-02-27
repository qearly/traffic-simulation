#include "Map.h"

using namespace std;

Map::Map(TrafficSimDataParser *db)
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
	
}

Road * Map::getRoad(double x, double y, double dir)
{
	
}

void Map::addIntersection(Intersection * i)
{

}

Intersection * Map::getIntersection(int id)
{
	
}

Intersection * Map::getNextIntersection(double x, double y, double dir)
{
	
}

Intersection * Map::getIntersection(double x, double y)
{
	
}

void Map::PrintReport()
{

}

void Map::upDate(double time)
{

}
