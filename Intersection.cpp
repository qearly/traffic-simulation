#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 


#include "Intersection.h"
#include "Road.h"
#include "TrafficLight.h"
#include "TrafficSimDataParser.h"

using namespace std;

Intersection::Intersection()
{
	intersectionID = 0;
	xCenterPoint = 0.0;
	yCenterPoint = 0.0;
	xIntersectCoord = 0.0;
	yIntersectCoord = 0.0;
	NumLanesNS = 0;
	NumLanesEW = 0;
}

Intersection::~Intersection()
{

}

bool Intersection::isPointInIntersection(double xCenterPoint, double yCenterPoint)
{
	Road *rInst = new Road();
	double laneWidth = 36.6;

	double xUpperLeft = xCenterPoint - (rInst->getLaneNumber() / 2 * laneWidth);
	double yUpperLeft = yCenterPoint - (rInst->getLaneNumber() / 2 * laneWidth);
	double xLowerRight = xCenterPoint + (rInst->getLaneNumber() / 2 * laneWidth);
	double yLowerRight = yCenterPoint + (rInst->getLaneNumber() / 2 * laneWidth);

	if ((xCenterPoint >= xUpperLeft) && (xCenterPoint <= xLowerRight) && (yCenterPoint >= yUpperLeft) && (yCenterPoint <= yLowerRight))
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

// No need to loop through intersection because the lights
// at each intersection are synced
void Intersection::intersectUpDate(TrafficLight *light)
{
	light->NSLightUpDate();
	light->EWLightUpDate();
}

void Intersection::setIntersectionID(int ID)
{
	intersectionID = ID;
}

void Intersection::setxCenterPoint(double point)
{
	xCenterPoint = point;
}

void Intersection::setyCenterPoint(double point)
{
	yCenterPoint = point;
}

void Intersection::setxIntersectCoord(double x)
{
	xIntersectCoord = x;
}

void Intersection::setyIntersectCoord(double y)
{
	yIntersectCoord = y;
}

void Intersection::setNumLanesNS(int num)
{
	NumLanesNS = num;
}

void Intersection::setNumLanesEW(int num)
{
	NumLanesEW = num;
}

void Intersection::setNameN(char * name)
{
	strcpy(nameN, name);
}

void Intersection::setNameS(char * name)
{
	strcpy(nameS, name);
}

void Intersection::setNameE(char * name)
{
	strcpy(nameE, name);
}

void Intersection::setNameW(char * name)
{
	strcpy(nameW, name);
}

void Intersection::setCurRoad(char * road)
{
	strcpy(curRoad, road);
}

void Intersection::setIntersectionData(int intersectID, double xPosition, double yPosition, char * north, char * east, char * south, char * west)
{
	intersectionID = intersectID;
	xCenterPoint = xPosition;
	yCenterPoint = yPosition;
	strcpy(nameN, north);
	strcpy(nameE, east);
	strcpy(nameS, south);
	strcpy(nameW, west);
}

int Intersection::getIntersectionID()
{
	return intersectionID;
}

double Intersection::getxCenterPoint()
{
	return xCenterPoint;
}

double Intersection::getyCenterPoint()
{
	return yCenterPoint;
}

double Intersection::getxIntersectCoord()
{
	return xIntersectCoord;
}

double Intersection::getyIntersectCoord()
{
	return yIntersectCoord;
}

int Intersection::getNumLanesNS()
{
	return NumLanesNS;
}

int Intersection::getNumLanesEW()
{
	return NumLanesEW;
}

char * Intersection::getNameN()
{
	return nameN;
}

char * Intersection::getNameS()
{
	return nameS;
}

char * Intersection::getNameE()
{
	return nameE;
}

char * Intersection::getNameW()
{
	return nameW;
}

char * Intersection::getCurRoad()
{
	return curRoad;
}
