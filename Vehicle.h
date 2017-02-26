#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <string>

class Vehicle
{
	private:
		string type;
		int carID;
		double xIntersectStartPoint;
		double yIntersectStartPoint;
		int intersectStartDirection;
		double intersectAcceleration;
		double intersectSpeed;
		double xintersectLocation;
		double yintersectLocation;

	public:
		void Move();
		void PrintReport();

		void setType(string name);
		void setCarID(int ID);
		string getType();
		int getCarID();

		void setxIntersectStartPoint(double start);
		void setyIntersectStartPoint(double start);
		void setIntersectStartDirection(int start);
		void setIntersectAcceleration(double acceleration);
		void setIntersectSpeed(double speed);
		void setxIntersectLocation(double location);
		void setyIntersectLocation(double location);

		double getxIntersectionStartPoint();
		double getyIntersectionStartPoint();
		int getIntersectStartDirection();
		double getIntersectAcceleration();
		double getIntersectSpeed();
		double getxIntersectLocation();
		double getyIntersectLocation();

};


#endif
