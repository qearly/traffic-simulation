/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: TrafficLightManager.h
*   Author: Matt Stewart
*   Desc: Traffic Light header file
*   Date: 3-19-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/

#ifndef TrafficLightManager_H_
#define TrafficLightManager_H_

#include "Intersection.h"
#include <sys/types.h>     
#include <sys/timeb.h>     
#include <time.h> 

enum LightState { GREEN, RED, YELLOW };
class Intersection;

class TrafficLightManager
{
	private:
		struct _timeb tStruct;
		double thisTime;
		double outputTime;
		bool done;
		int counter;
		int counterEW;
		Intersection *intersectInstance;

	protected:
		LightState NSState;
		LightState EWState;

	public:
		void UpDate();
		void NSLightUpDate();
		void EWLightUpDate();
		void PrintLight();
		LightState getNSState();
		LightState getEWState();
		void setNSState(LightState state);
		void setEWState(LightState state);
};


#endif
