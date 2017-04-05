#pragma once


#include "Vehicle.h"

class VehicleFactory
{
	private:
		VehicleFactory();

	public:
		~VehicleFactory();
		virtual Vehicle *getVehicle(char *name);
		virtual Vehicle *getInstance();
		virtual Vehicle *createVehicle();
};