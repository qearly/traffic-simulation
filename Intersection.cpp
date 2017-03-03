#include "Intersection.h"
#include "Road.h"
#include "TrafficLight.h"

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
	nameN = NULL;
	nameS = NULL;
	nameE = NULL;
	nameW = NULL;
	curRoad = NULL;
}

Intersection::~Intersection()
{

}

bool Intersection::isPointInIntersection()
{
	Road *road = new Road();

	double xUpperLeft = xCenterPoint - (road->getLaneNumber() / 2 * 36.6);
	double yUpperLeft = yCenterPoint - (road->getLaneNumber() / 2 * 36.6);
	double xLowerRight = xCenterPoint + (road->getLaneNumber() / 2 * 36.6);
	double yLowerRight = yCenterPoint + (road->getLaneNumber() / 2 * 36.6);

	if ((xCenterPoint >= xUpperLeft) && (xCenterPoint <= xLowerRight) && (yCenterPoint >= yUpperLeft) && (yCenterPoint <= yLowerRight))
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

void Intersection::upDate()
{
	TrafficLight* lightUpdate = new TrafficLight();
	lightUpdate->trafficUpDate();
}

void Intersection::setIntersectionID(int ID)
{
	intersectionID = ID;
}

void Intersection::setxCenterPoint(int point)
{
	xCenterPoint = point;
}

void Intersection::setyCenterPoint(int point)
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

void Intersection::setNameNS(char *name)
{
	strcpy(nameNS, name);
}

void Intersection::setNameEW(char *name)
{
	strcpy(nameEW, name);
}

int Intersection::getIntersectionID()
{
	return intersectionID;
}

int Intersection::getxCenterPoint()
{
	return xCenterPoint;
}

int Intersection::getyCenterPoint()
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

char* Intersection::getNameNS()
{
	return nameNS;
}

char* Intersection::getNameEW()
{
	return nameEW;
}
