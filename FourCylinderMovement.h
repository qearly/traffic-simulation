#pragma once

#include "Movement.h"
#include "TrafficLight.h"
#include "Road.h"
#include "TrafficSimDataParser.h"
#include "Map.h"


class FourCylinderMovement : public Movement
{
	private:
		int counter;
		int max;
		double value;
		bool turnDecided = false;
		enum turnState { LEFT, STRAIGHT, RIGHT };
		TrafficLight *light;
		Road *road;
		TrafficSimDataParser *dp;
		Intersection *intersection;
		Map *mapInst;
		Intersection *nextIntersection;

	protected:
		turnState turnDirection;

	public:
		void Move(char *filename);
		void PrintStatus();
};
