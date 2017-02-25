#include "Road.h"

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
	double yLowerLeft;

	// For North-South
	xUpperLeft = getxRoadStart() - ((laneNumber / 2) * 3.6);
	yUpperLeft = getyRoadStart();
	xLowerRight = getxRoadEnd() + ((laneNumber / 2) * 3.6);
	yLowerLeft = getyRoadEnd();
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

int Road::getSpeedLimit()
{
	return speedLimit;
}
