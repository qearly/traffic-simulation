#include "VehicleFactory.h"

VehicleFactory::VehicleFactory()
{

}

VehicleFactory::~VehicleFactory()
{

}

Vehicle * VehicleFactory::getVehicle(char * name)
{
	return nullptr;
}

Vehicle * VehicleFactory::getInstance()
{
	return nullptr;
}

Vehicle * VehicleFactory::createVehicle(char *type, char *filename)
{
	Vehicle *vehicle = new Vehicle();
	TrafficSimDataParser *dp = TrafficSimDataParser::getInstance();
	dp->setDataFileName(filename);

	char vehicleType[64];
	int carID;
	double xVehicleLocation;
	double yVehicleLocation;
	double direction;
	double Acceleration;

	if ((strcmp(type, "4-CYLINDER_CAR") == 0))
	{
		for (int i = 0; i < dp->getVehicleCount(); i++)
		{

			if (dp->getVehicleData(vehicleType, &carID, &xVehicleLocation, &yVehicleLocation, &direction, &Acceleration))
			{
				vehicle->setType(vehicleType);
				vehicle->setCarID(carID);
				vehicle->setxVehicleLocation(xVehicleLocation);
				vehicle->setyVehicleLocation(yVehicleLocation);
				vehicle->setDirection(direction);
				vehicle->setAcceleration(Acceleration);

				if ((strcmp(vehicle->getType(), "4-CYLINDER_CAR") == 0))
				{
					return vehicle;
				}
			}
		}
	}

	else if ((strcmp(type, "6-CYLINDER_CAR") == 0))
	{
		for (int i = 0; i < dp->getVehicleCount(); i++)
		{

			if (dp->getVehicleData(vehicleType, &carID, &xVehicleLocation, &yVehicleLocation, &direction, &Acceleration))
			{
				vehicle->setType(vehicleType);
				vehicle->setCarID(carID);
				vehicle->setxVehicleLocation(xVehicleLocation);
				vehicle->setyVehicleLocation(yVehicleLocation);
				vehicle->setDirection(direction);
				vehicle->setAcceleration(Acceleration);

				if ((strcmp(vehicle->getType(), "6-CYLINDER_CAR") == 0))
				{
					return vehicle;
				}
			}
		}
	}

	else if ((strcmp(type, "8-CYLINDER_CAR") == 0))
	{
		for (int i = 0; i < dp->getVehicleCount(); i++)
		{
		
			if (dp->getVehicleData(vehicleType, &carID, &xVehicleLocation, &yVehicleLocation, &direction, &Acceleration))
			{
				vehicle->setType(vehicleType);
				vehicle->setCarID(carID);
				vehicle->setxVehicleLocation(xVehicleLocation);
				vehicle->setyVehicleLocation(yVehicleLocation);
				vehicle->setDirection(direction);
				vehicle->setAcceleration(Acceleration);

				if ((strcmp(vehicle->getType(), "8-CYLINDER_CAR") == 0))
				{
					return vehicle;
				}
			}
		}
	}

	else if ((strcmp(type, "LARGE_TRUCK") == 0))
	{
		for (int i = 0; i < dp->getVehicleCount(); i++)
		{

			if (dp->getVehicleData(vehicleType, &carID, &xVehicleLocation, &yVehicleLocation, &direction, &Acceleration))
			{
				vehicle->setType(vehicleType);
				vehicle->setCarID(carID);
				vehicle->setxVehicleLocation(xVehicleLocation);
				vehicle->setyVehicleLocation(yVehicleLocation);
				vehicle->setDirection(direction);
				vehicle->setAcceleration(Acceleration);

				if ((strcmp(vehicle->getType(), "LARGE_TRUCK") == 0))
				{
					return vehicle;
				}
			}
		}
	}

	else if ((strcmp(type, "18-WHEELER") == 0))
	{
		for (int i = 0; i < dp->getVehicleCount(); i++)
		{
			
			if (dp->getVehicleData(vehicleType, &carID, &xVehicleLocation, &yVehicleLocation, &direction, &Acceleration))
			{
				vehicle->setType(vehicleType);
				vehicle->setCarID(carID);
				vehicle->setxVehicleLocation(xVehicleLocation);
				vehicle->setyVehicleLocation(yVehicleLocation);
				vehicle->setDirection(direction);
				vehicle->setAcceleration(Acceleration);

				if ((strcmp(vehicle->getType(), "18-WHEELER") == 0))
				{
					return vehicle;
				}
			}
		}
	}

	return nullptr;
}
