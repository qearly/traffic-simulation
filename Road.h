#ifndef ROAD_H_
#define ROAD_H_

#include <string>

class Road
{
	private:
		string roadName;
		double xStartPoint;
		double yStartPoint;
		double xEndpoint;
		double yEndPoint;
		int laneNumber;
		int startIntersection;
		int endIntersection;
		int speedLimit;

	public:
		bool isPointOnRoad();

		void setxRoadStart (double startingPoint);
		void setxRoadEnd(double endingPoint);
		void setyRoadStart(double startingPoint);
		void setyRoadEnd(double endingPoint);
		void setLaneNumber(int lane);
		void setStartIntersection(int startingPoint);
		void setEndIntersection(int endingPoint);
		void setSpeedLimit(int limit);

		double getxRoadStart();
		double getxRoadEnd();		
		double getyRoadEnd();
		double getyRoadEnd();
		int getLaneNumber();		
		int getStartIntersection();		
		int getEndIntersection();		
		int getSpeedLimit();
};



#endif
