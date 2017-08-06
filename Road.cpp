/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Road.cpp
*   Author: Matt Stewart
*   Desc: Implementation file for the Road class, contains behaviors and information for road objects.
*   Date: 3-19-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/



#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 


#include "Road.h"
#include "Map.h"
#include "TrafficSimDataParser.h"
#include <vector>

using namespace std;

Road::Road()
{
	xStartPoint = 0.0;
	yStartPoint = 0.0;
    xEndPoint = 0.0;
	yEndPoint = 0.0;
	laneNumber = 0;
	startIntersection = 0;
	endIntersection = 0;
	speedLimitMPS = 0.0;
	speedLimitMPH = 0.0;
}

Road::~Road()
{

}

// Returns true if the x and y values passed in are on instance of Road
bool Road::isPointOnRoad(double xCoord, double yCoord, double direction, char *filename)
{
	double xUpperLeft;
	double yUpperLeft;
	double xLowerRight;
	double yLowerRight;
	TrafficSimDataParser *dp = TrafficSimDataParser::getInstance();
	dp->setDataFileName(filename);
	int numberRoads = dp->getRoadCount();

	int intersectID = 0;
	Map *vec = new Map(filename);
	
	for (int i = 0; i < numberRoads; i++)
	{
	
		if ((direction == 0.0) || (direction == 180.0))
		{ 
			// For North-South
			xUpperLeft = xStartPoint - ((laneNumber / 2) * 3.6);
			yUpperLeft = yStartPoint;
			xLowerRight = xEndPoint + ((laneNumber / 2) * 3.6);
			yLowerRight = yEndPoint;

			if ((xCoord >= xUpperLeft) && (xCoord <= xLowerRight) && (yCoord >= yUpperLeft) && (yCoord <= yLowerRight))
			{
				return true;
			}

			else
			{
				return false;
			}

		}

		else if ((direction == 90.0) || (direction == 270.0))
		{
			// For East-West
			xUpperLeft = xStartPoint;
			yUpperLeft = yStartPoint - ((laneNumber / 2) * 3.6);
			xLowerRight = xEndPoint;
			yLowerRight = yEndPoint - ((laneNumber / 2) * 3.6);

			if ((xCoord >= xUpperLeft) && (xCoord <= xLowerRight) && (yCoord >= yUpperLeft) && (yCoord <= yLowerRight))
			{
				return true;
			}

			else

			{
				return false;
			}
		}
	}

	return true;
}

void Road::setRoadName(char *name)
{
	strcpy(roadName, name);
}

char * Road::getRoadName()
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

void Road::setLaneNumber(int lane)
{
	laneNumber = lane;
}

void Road::setLaneNumberEW(int lane)
{
}

double Road::getyRoadEnd()
{
	return yEndPoint;
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

void Road::setSpeedLimitMPH(double limit)
{
	speedLimitMPH = limit;
}

int Road::getEndIntersection()
{
	return endIntersection;
}

void Road::setSpeedLimitMPS(double limit)
{
	speedLimitMPS = limit;
}

void Road::setDirection(double dir)
{
	direction = dir;
}

void Road::setRoadData(char * name, double xStart, double yStart, double xEnd, double yEnd, int intersectStart, int intersectEnd, double speedLimit, int numLanes)
{
	strcpy(roadName, name);

	xStartPoint = xStart;
	yStartPoint = yStart;
	xEndPoint = xEnd;
	yEndPoint = yEnd;
	startIntersection = intersectStart;
	endIntersection = intersectEnd;
	speedLimitMPH = speedLimit;
	laneNumber = numLanes;
}

double Road::getSpeedLimitMPS()
{
	return speedLimitMPS;
}

double Road::getSpeedLimitMPH()
{
	return speedLimitMPH;
}

double Road::getDirection()
{
	return direction;
}
