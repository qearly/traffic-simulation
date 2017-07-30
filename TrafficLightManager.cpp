/*******************************************************************
*   CS 307 Programming Assignment 2
*   File: TrafficLightManager.cpp
*   Author: Matt Stewart
*   Desc: TrafficLightManager class that handles the traffic light states
*   Date: 3-19-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/

#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS 


#include "TrafficLightManager.h"
#include <sys/types.h>     
#include <sys/timeb.h>     
#include <time.h>   
#include <iostream>      

using namespace std;

void TrafficLightManager::UpDate()
{
	NSLightUpDate();
	EWLightUpDate();
}

void TrafficLightManager::NSLightUpDate()
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

void TrafficLightManager::EWLightUpDate()
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

void TrafficLightManager::PrintLight()
{
	if (NSState == 0)
	{
		cout << "North/South traffic lights are currently GREEN" << endl;
	}

	else if (NSState == 1)
	{
		cout << "North/South traffic lights are currently RED" << endl;
	}

	else if (NSState == 2)
	{
		cout << "North/South traffic lights are currently YELLOW" << endl;
	}

	if (EWState == 0)
	{
		cout << "East/West traffic lights are currently GREEN" << endl << endl;
	}

	else if (EWState == 1)
	{
		cout << "East/West traffic lights are currently RED" << endl << endl;
	}

	else if (EWState == 2)
	{
		cout << "East/West traffic lights are currently YELLOW" << endl << endl;
	}
}

LightState TrafficLightManager::getNSState()
{
	return NSState;
}

LightState TrafficLightManager::getEWState()
{
	return EWState;
}

void TrafficLightManager::setNSState(LightState state)
{
	this->NSState = state;
}

void TrafficLightManager::setEWState(LightState state)
{
	this->EWState = state;
}





