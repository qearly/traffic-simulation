#include "TrafficLight.h"

using namespace std;

void TrafficLight::trafficUpDate()
{

}

TrafficLight::LightState TrafficLight::getNSState()
{
	if (GREEN == true)
	{
		// Start timer for GREEN
		// Once timer passes the alloted time for a green light, set GREEN to false
	}

	else if (RED == true)
	{
		// Start timer for RED
		// Once timer passes the alloted time for a red light, set red to false
	}

	else if (YELLOW == true)
	{
		// Start timer for YELLOW
		// Once timer passes the alloted time for a yellow light, set YELLOW to false
	}
}

TrafficLight::LightState TrafficLight::getEWState()
{
	if (GREEN == true)
	{
		// Start timer for GREEN
		// Once timer passes the alloted time for a green light, set GREEN to false

		return GREEN;
	}

	else if (RED == true)
	{
		// Start timer for RED
		// Once timer passes the alloted time for a red light, set red to false

		return RED;
	}

	else if (YELLOW == true)
	{
		// Start timer for YELLOW
		// Once timer passes the alloted time for a yellow light, set YELLOW to false
	}
}
