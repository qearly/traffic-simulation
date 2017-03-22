#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 


#include "TrafficLight.h"  
#include <iostream>      

using namespace std;

void TrafficLight::NSLightUpDate()
{
	
	if (counter > 100)
	{
		counter = 0;
	}


	if (counter <= 100)  
	{
			counter += 1;

			if (counter <= 50)
			{
				setNSState(RED);
			}

			else if ((counter > 50) && (counter <= 95))
			{
				setNSState(GREEN);
			}

			else if ((counter > 95) && (counter <= 100))
			{
				setNSState(YELLOW);
			}

		
	}

}

void TrafficLight::EWLightUpDate()
{

	if (counterEW > 100)
	{
		counterEW = 0;
	}


	if (counterEW <= 100)
	{
	
			counterEW += 1;
		
			if (counterEW <= 45)
			{
				setEWState(GREEN);

			}

			else if ((counterEW > 45) && (counterEW <= 50))
			{
				setEWState(YELLOW);
			}

			else if ((counterEW > 50) && (counterEW <= 100))
			{
				setEWState(RED);
			}


	}
}

LightState TrafficLight::getNSState()
{

	return NSState;
}

LightState TrafficLight::getEWState()
{
	return EWState;
}

void TrafficLight::setNSState(LightState state)
{
	this->NSState = state;
}

void TrafficLight::setEWState(LightState state)
{
	this->EWState = state;
}
