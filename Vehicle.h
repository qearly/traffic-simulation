#ifndef VEHICLE_H_
#define VEHICLE_H_



class Vehicle
{
	private:
		char type[64];
		int carID;
		double xVehicleStartPoint;
		double yVehicleStartPoint;
		int startDirection;
		double Acceleration;
		double speedMPH;
		double speedMPS;
		double xVehicleLocation;
		double yVehicleLocation;

	public:
		void Move();
		void PrintReport();
		void setVehicleSpeed(double mps, double mph);
		void setType(char *name);
		void setCarID(int ID);
		char * getType();
		int getCarID();

		void setxVehicleStartPoint(double start);
		void setyVehicleStartPoint(double start);
		void setStartDirection(int start);
		void setAcceleration(double acceleration);
		void setSpeedMPS(double speed);
		void setSpeedMPH(double speed);
		void setxVehicleLocation(double location);
		void setyVehicleLocation(double location);

		double getSpeedMPS();
		double getSpeedMPH();
		double getxVehicleStartPoint();
		double getyVehicleStartPoint();
		int getStartDirection();
		double getAcceleration();
		double getSpeed();
		double getxVehicleLocation();
		double getyVehicleLocation();

};
