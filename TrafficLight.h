#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include "Intersection.h"

class TrafficLight
{
	private:
		Intersection *intersectInstance;
		enum LightState
		{
			green,
			red,
			yellow
		};

	public:
		void upDate();
		LightState getNSState();
		LightState getEWState();
};


#endif
