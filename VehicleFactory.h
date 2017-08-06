#pragma once


#include "Vehicle.h"

class VehicleFactory
{
	private:
		

	public:
		VehicleFactory();
		~VehicleFactory();
		virtual Vehicle *getVehicle(char *name);
		virtual Vehicle *getInstance();
		Vehicle *createVehicle(char *type, char *filename);
};