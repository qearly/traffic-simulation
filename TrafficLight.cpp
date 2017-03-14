#include "TrafficLight.h"
#include <sys/types.h>     
#include <sys/timeb.h>     
#include <time.h>   
#include <iostream>      

using namespace std;

void TrafficLight::trafficUpDate()
{
	thisTime = 0;
	outputTime = 0;

	if (getNSState() == NULL)
	{
		setNSState(GREEN);
	}
	
	if (getEWState() == NULL)
	{
		setEWState(RED);
	}


	// Starting the NS timer. We'll see if this works.
	_ftime(&tStruct);
	thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); 
	outputTime = thisTime + 5.0; 

	if (getNSState() == GREEN)
	{
		while (outputTime <= 45)
		{
			_ftime(&tStruct);
			thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); 

			if (thisTime >= outputTime)
			{
				outputTime += 5.0;
				cout << "The current state of NS light is Green." << endl;
			}
		}

		outputTime = 0;
		setNSState(YELLOW);
	}

	else if (getNSState() == YELLOW)
	{
		while (outputTime <= 5)
		{
			_ftime(&tStruct);
			thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);

			if (thisTime >= outputTime)
			{
				outputTime += 5.0;
				cout << "The current state of NS light is Yellow." << endl;
			}
		}

		outputTime = 0;
		setNSState(RED);
	}

	else if (getNSState() == RED)
	{
		while (outputTime <= 50)
		{
			_ftime(&tStruct);
			thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);

			if (thisTime >= outputTime)
			{
				outputTime += 5.0;
				cout << "The current state of NS light is Red." << endl;
			}
		}

		outputTime = 0;
		setNSState(GREEN);
	}
	// End the NS timer


	// Starting the EW timer. We'll see if this works.
	_ftime(&tStruct);
	thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);
	outputTime = thisTime + 5.0;

	if (getEWState() == RED)
	{
		while (outputTime <= 50)
		{
			_ftime(&tStruct);
			thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);

			if (thisTime >= outputTime)
			{
				outputTime += 5.0;
				cout << "The current state of EW light is RED." << endl;
			}
		}

		outputTime = 0;
		setNSState(GREEN);
	}

	else if (getNSState() == GREEN)
	{
		while (outputTime <= 5)
		{
			_ftime(&tStruct);
			thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);

			if (thisTime >= outputTime)
			{
				outputTime += 5.0;
				cout << "The current state of EW light is GREEN." << endl;
			}
		}

		outputTime = 0;
		setNSState(YELLOW);
	}

	else if (getNSState() == YELLOW)
	{
		while (outputTime <= 5)
		{
			_ftime(&tStruct);
			thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0);

			if (thisTime >= outputTime)
			{
				outputTime += 5.0;
				cout << "The current state of NS light is YELLOW." << endl;
			}
		}

		outputTime = 0;
		setNSState(RED);
	}
}

LightState TrafficLight::getNSState()
{

	// Set state to Green
	// While timer is less than 45
	// Then set to yellow
	// etc etc
	trafficUpDate();
	return state;
}

LightState TrafficLight::getEWState()
{
	// Set state to Red
	// While timer is less than 50
	// Then set to green
	// etc etc
	trafficUpDate();
	return state;
}

void TrafficLight::setNSState(LightState state)
{
	this->state = state;
}

void TrafficLight::setEWState(LightState state)
{
	this->state = state;
}
