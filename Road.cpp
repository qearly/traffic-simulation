#include "Road.h"
#include "Map.h"
#include "TrafficSimDataParser.h"
#include <vector>

using namespace std;

Road::Road()
{

}

Road::~Road()
{

}

bool Road::isPointOnRoad()
{
	double xUpperLeft;
	double yUpperLeft;
	double xLowerRight;
	double yLowerRight;

	vector<Road*>::iterator it;
	Map *vec;
	
	for (it = vec->roadCollection.begin(); it <= vec->roadCollection.end(); it++)
	{
		getxRoadStart();
		getyRoadStart();
		getxRoadEnd();
		getyRoadEnd();
		getxCoord();
		getyCoord();
		getLaneNumber();
		getDirectionNS();
		getDirectionEW();

		if (directionNS = true)
		{ 
			// For North-South
			xUpperLeft = getxRoadStart() - ((getLaneNumber() / 2) * 3.6);
			yUpperLeft = getyRoadStart();
			xLowerRight = getxRoadEnd() + ((getLaneNumber() / 2) * 3.6);
			yLowerRight = getyRoadEnd();

			if ((getxCoord() >= xUpperLeft) && (getxCoord() <= xLowerRight) && (getyCoord() >= yUpperLeft) && (getyCoord() <= yLowerRight))
			{
				return true;
			}

		}

		else if (directionEW = true)
		{
			// For East-West
			xUpperLeft = getxRoadStart();
			yUpperLeft = getyRoadStart() - ((getLaneNumber() / 2) * 3.6);
			xLowerRight = getyRoadEnd();
			yLowerRight = getyRoadEnd() - ((getLaneNumber() / 2) * 3.6);

			if ((getxCoord() >= xUpperLeft) && (getxCoord() <= xLowerRight) && (getyCoord() >= yUpperLeft) && (getyCoord() <= yLowerRight))
			{
				return true;
			}
		}
	}

	
}

void Road::setDirectionNS(bool value)
{
	directionNS = value;
}

void Road::setDirectionEW(bool value)
{
	directionEW = value;
}

bool Road::getDirectionNS()
{
	return directionNS;
}

bool Road::getDirectionEW()
{
	return directionEW;
}

void Road::setRoadName(string name)
{
	roadName = name;
}

string Road::getRoadName()
{
	return roadName;
}

void Road::setxRoadStart(double startingPoint)
{
	xStartPoint = startingPoint;
}

double Road::getxRoadStart()
{
	return xStartPoint;
}

void Road::setyRoadStart(double startingPoint)
{
	yStartPoint = startingPoint;
}

double Road::getyRoadStart()
{
	return yStartPoint;
}

void Road::setxRoadEnd(double endingPoint)
{
	xEndPoint = endingPoint;
}

double Road::getxRoadEnd()
{
	return xEndPoint;
}

void Road::setyRoadEnd(double endingPoint)
{
	yEndPoint = endingPoint;
}

double Road::getyRoadEnd()
{
	return yEndPoint;
}

void Road::setLaneNumber(int lane)
{
	laneNumber = lane;
}

int Road::getLaneNumber()
{
	return laneNumber;
}

void Road::setStartIntersection(int startingPoint)
{
	startIntersection = startingPoint;
}

int Road::getStartIntersection()
{
	return startIntersection;
}

void Road::setEndIntersection(int endingPoint)
{
	endIntersection = endingPoint;
}

int Road::getEndIntersection()
{
	return endIntersection;
}

void Road::setSpeedLimit(int limit)
{
	speedLimit = limit;
}

void Road::setxCoord(double x)
{
	xCoord = x;
}

void Road::setyCoord(double y)
{
	yCoord = y;
}

int Road::getSpeedLimit()
{
	return speedLimit;
}

double Road::getxCoord()
{
	return xCoord;
}

double Road::getyCoord()
{
	return yCoord;
}
