/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Vehicle.h
*   Author: Matt Stewart
*   Desc: Vehicle header file
*   Date: 3-19-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "FourCylinderMovement.h"
#include "SixCylinderMovement.h"
#include "EightCylinderMovement.h"
#include "WheelerMovement.h"
#include "TruckMovement.h"
#include "TrafficLightManager.h"
#include "Road.h"
#include "TrafficSimDataParser.h"
#include "Map.h"

class FourCylinderMovement;
class SixCylinderMovement;
class EightCylinderMovement;
class WheelerMovement;
class TruckMovement;

class Vehicle
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
		int counter;
		int max;
		double value;
		bool turnDecided;
		enum turnState { LEFT, STRAIGHT, RIGHT };
		TrafficLightManager *light;
		Road *road;
		TrafficSimDataParser *dp;
		Intersection *intersection;
		Map *mapInst;
		Intersection *nextIntersection;
		FourCylinderMovement *fourVehicle;
		SixCylinderMovement *sixVehicle;
		EightCylinderMovement *eightVehicle;
		WheelerMovement *wheelerVehicle;
		TruckMovement *truckVehicle;

	protected:
		turnState turnDirection;

	public:
		Vehicle();
		~Vehicle();
		void CallMove(char *filename);
		void CallPrintStatus();
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


#endif
