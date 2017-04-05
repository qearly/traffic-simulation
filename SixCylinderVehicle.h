#pragma once

/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Vehicle.h
*   Author: Matt Stewart
*   Desc: Vehicle header file
*   Date: 3-19-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/

#include "Vehicle.h"
#include "includes.h"

class SixCylinderVehicle : public Vehicle
{
private:
	char type[64];
	int carID;
	double direction;
	double Acceleration;
	double speedMPH;
	double speedMPS;
	double xVehicleLocation;
	double yVehicleLocation;
	int counter = 0;
	int max = 100;
	double value;
	bool turnDecided = false;
	enum turnState { LEFT, STRAIGHT, RIGHT };
	TrafficLight *light = new TrafficLight();
	Road *road = new Road();
	TrafficSimDataParser *dp;
	Intersection *intersection = new Intersection();
	Map *mapInst;
	Intersection *nextIntersection;

protected:
	turnState turnDirection;

public:
	SixCylinderVehicle();
	~SixCylinderVehicle();
	void Move(char *filename);
	void PrintStatus();
	void setType(char *name);
	void setCarID(int ID);
	char * getType();
	int getCarID();

	void setDirection(double direc);
	void setAcceleration(double acceleration);
	void setSpeedMPS(double speed);
	void setSpeedMPH(double speed);
	void setxVehicleLocation(double location);
	void setyVehicleLocation(double location);

	double getSpeedMPS();
	double getSpeedMPH();
	double getDirection();
	double getAcceleration();
	double getxVehicleLocation();
	double getyVehicleLocation();

};
