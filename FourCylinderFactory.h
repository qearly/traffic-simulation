#pragma once


#include "VehicleFactory.h"
#include "4CylinderVehicle.h"

class FourCylinderFactory : public VehicleFactory
{
	private:
		FourCylinderFactory();
		vector<FourCylinderVehicle*>fourCollect;

	public:
		~FourCylinderFactory();
		static FourCylinderFactory *getInstance();
		Vehicle *getVehicle(char *name);
		Vehicle *createVehicle();
};