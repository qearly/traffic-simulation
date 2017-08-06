/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Road.h
*   Author: Matt Stewart
*   Desc: Road header file
*   Date: 3-19-2017
*
*   I attest that this program is entirely my own work
*******************************************************************/

#ifndef ROAD_H_
#define ROAD_H_

class Road
{
	private:
		char roadName[64];
		double xStartPoint;
		double yStartPoint;
		double xEndPoint;
		double yEndPoint;
		int laneNumber;
		int startIntersection;
		int endIntersection;
		double speedLimitMPS;
		double speedLimitMPH;
		double direction;

	public:
		Road();
		~Road();
		bool isPointOnRoad(double xCoord, double yCoord, double direction, char *filename);
		void setRoadName(char *name);
		void setxRoadStart(double startingPoint);
		void setxRoadEnd(double endingPoint);
		void setyRoadStart(double startingPoint);
		void setyRoadEnd(double endingPoint);
		void setLaneNumber(int lane);
		void setLaneNumberEW(int lane);
		void setStartIntersection(int startingPoint);
		void setEndIntersection(int endingPoint);
		void setSpeedLimitMPS(double limit);
		void setSpeedLimitMPH(double limit);
		void setDirection(double dir);
		void setRoadData(char *name, double xStart, double yStart, double xEnd, double yEnd, int intersectStart, int intersectEnd, double speedLimit, int numLanes);

		char * getRoadName();
		double getxRoadStart();
		double getxRoadEnd();		
		double getyRoadStart();
		double getyRoadEnd();
		int getLaneNumber();	
		int getStartIntersection();		
		int getEndIntersection();		
		double getSpeedLimitMPS();
		double getSpeedLimitMPH();
		double getDirection();
};



#endif
