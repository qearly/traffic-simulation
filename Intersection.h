#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <string>

class Intersection
{
	private:
		int intersectionID;
		int xCenterPoint;
		int yCenterPoint;
		string nameNS;
		string nameEW;

	public:
		bool isPointInIntersection();
		void upDate();

		void setIntersectionID(int ID);
		void setxCenterPoint(int point);
		void setyCenterPoint(int point);
		void setNameNS(string name);
		void setNameEW(string name);

		int getIntersectionID();
		int getxCenterPoint();
		int getyCenterPoint();
		string getNameNS();
		string getNameEW();
};

#endif
