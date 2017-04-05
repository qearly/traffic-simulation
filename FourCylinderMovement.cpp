#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 


#include "FourCylinderMovement.h"
#include "TrafficLight.h"
#include "Map.h"
#include "Road.h"
#include <stdlib.h>
#include <sys/types.h>    
#include <sys/timeb.h>     
#include <time.h>

using namespace std;

FourCylinderMovement::FourCylinderMovement()
{
	counter = 0;
	max = 100;
	value = 0;
	light = new TrafficLight();
	road = new Road();
	intersection = new Intersection();
	nextIntersection = new Intersection();
}

FourCylinderMovement::~FourCylinderMovement()
{

}

void FourCylinderMovement::Move(char *filename)
{

}