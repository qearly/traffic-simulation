#ifndef ROAD_H_
#define ROAD_H_

class Road
{
  private:
		string roadName;
		int startPoint;
		int endpoint;
		int laneNumber;
		int startIntersection;
		int endIntersection;
		int speedLimit;

	public:
		bool isPointOnRoad();
};





#endif
