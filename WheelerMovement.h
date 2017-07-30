#pragma once

#include "Vehicle.h"
#include "Movement.h"
#include "TrafficLightManager.h"
#include "Road.h"
#include "TrafficSimDataParser.h"
#include "Map.h"

class Vehicle;
class WheelerMovement : public Movement
{
	private:
		int counter;
		int max;
		double value;
		bool turnDecided;
		enum turnState { LEFT, STRAIGHT, RIGHT };
		Vehicle *vehicle;
		TrafficLightManager *light;
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