#ifndef ROAD_H_
#define ROAD_H_

#include <string>

class Road
{
	private:
		string roadName;
		bool directionNS;
		bool directionEW;
		double xStartPoint;
		double yStartPoint;
		double xEndPoint;
		double yEndPoint;
		double xCoord;
		double yCoord;
		int laneNumber;
		int startIntersection;
		int endIntersection;
		int speedLimit;

	public:
		Road();
		~Road();
		bool isPointOnRoad();
		void setDirectionNS(bool name);
		void setDirectionEW(bool name);
		bool getDirectionNS();
		bool getDirectionEW();

		void setRoadName(string name);
		void setxRoadStart(double startingPoint);
		void setxRoadEnd(double endingPoint);
		void setyRoadStart(double startingPoint);
		void setyRoadEnd(double endingPoint);
		void setLaneNumber(int lane);
		void setStartIntersection(int startingPoint);
		void setEndIntersection(int endingPoint);
		void setSpeedLimit(int limit);
		void setxCoord(double x);
		void setyCoord(double y);

		string getRoadName();
		double getxRoadStart();
		double getxRoadEnd();		
		double getyRoadStart();
		double getyRoadEnd();
		int getLaneNumber();		
		int getStartIntersection();		
		int getEndIntersection();		
		int getSpeedLimit();
		double getxCoord();
		double getyCoord();
};



#endif
