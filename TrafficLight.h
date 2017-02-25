#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include "Intersection.h"

class TrafficLight
{
	private:
		Intersection *intersectInstance;
		enum LightState {GREEN, RED, YELLOW};

	public:
		void upDate();
		LightState getNSState();
		LightState getEWState();
};


#endif
