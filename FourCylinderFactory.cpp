#include "FourCylinderFactory.h"

FourCylinderFactory::~FourCylinderFactory()
{

}

FourCylinderFactory * FourCylinderFactory::getInstance()
{
	static FourCylinderFactory *theInstance = NULL;

	if (theInstance == NULL)
	{
		theInstance = new FourCylinderFactory();
	}

	return theInstance;
}

Vehicle * FourCylinderFactory::getVehicle(char * name)
{
	for (size_t i = 0; i < fourCollect.size(); i++)
	{
		if (strcmp(fourCollect[i]->getType, name) == 0)
		{
			return fourCollect[i];
		}
	}

	return nullptr;
}

Vehicle * FourCylinderFactory::createVehicle()
{
	Vehicle *theVehicle = new FourCylinderVehicle();

	return theVehicle;
}
