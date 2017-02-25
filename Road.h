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
		void setRoadStart (int startingPoint);
		void setRoadEnd(int endingPoint);
		void setLaneNumber(int lane);
		void setStartIntersection(int startingPoint);
		void setEndIntersection(int endingPoint);
		void setSpeedLimit(int limit);
		int getRoadStart();
		int getRoadEnd();		
		int getLaneNumber();		
		int getStartIntersection();		
		int getEndIntersection();		
		int getSpeedLimit();
};





#endif
