#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <string>

class Intersection
{
	private:
		int intersectionID;
		double xCenterPoint;
		double yCenterPoint;
		double xIntersectCoord;
		double yIntersectCoord;
		int NumLanesNS;
		int NumLanesEW;
		char nameN[64];
		char nameS[64];
		char nameE[64];
		char nameW[64];
		char curRoad[64];

	public:
		Intersection();
		~Intersection();
		bool isPointInIntersection(double xCenterPoint, double yCenterPoint);
		void intersectUpDate(TrafficLight *light);
		void setIntersectionID(int ID);
		void setxCenterPoint(double point);
		void setyCenterPoint(double point);
		void setxIntersectCoord(double x);
		void setyIntersectCoord(double y);
		void setNumLanesNS(int num);
		void setNumLanesEW(int num);
		void setNameN(char *name);
		void setNameS(char *name);
		void setNameE(char *name);
		void setNameW(char *name);
		void setCurRoad(char *road);
		void setIntersectionData(int intersectID, double xPosition, double yPosition, char *north, char *east, char *south, char *west);

		int getIntersectionID();
		double getxCenterPoint();
		double getyCenterPoint();
		double getxIntersectCoord();
		double getyIntersectCoord();
		int getNumLanesNS();
		int getNumLanesEW();
		char *getNameN();
		char *getNameS();
		char *getNameE();
		char *getNameW();
		char *getCurRoad();
};

#endif
