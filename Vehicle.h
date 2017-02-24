#ifndef VEHICLE_H_
#define VEHICLE_H_

class Vehicle
{
  private:
		string type;
		int carID;
		int startPoint;
		int startDirection;
		double acceleration;
		int speed;
		int location;

	public:
		void Move();
		void PrintReport();
};


#endif
