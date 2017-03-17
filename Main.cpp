#include "includes.h"


using namespace std;

int main()
{
	char roadName[64];
	double xStart;
	double yStart;
	double xEnd;
	double yEnd;
	int intersectStart;
	int intersectEnd;
	double speedLimit;
	int numLanes;
	int intersectID;
	double xPosition;
	double yPosition;
	char nameN[32];
	char nameE[32];
	char nameS[32];
	char nameW[32];
	char type[64];
	int carID;
	double xVehicleLocation;
	double yVehicleLocation;
	double direction;
	double Acceleration;
	TrafficSimDataParser *dp = new TrafficSimDataParser("TrafficSim01.xml");
	Road *road = new Road();
	Map *map = new Map(dp);
	Vehicle *vehicle = new Vehicle();
	Intersection *intersection = new Intersection();
	dp->getRoadData(roadName, &xStart, &yStart, &xEnd, &yEnd, &intersectStart, &intersectEnd, &speedLimit, &numLanes);
	dp->getIntersectionData(&intersectID, &xPosition, &yPosition, nameN, nameE, nameS, nameW);
	dp->getVehicleData(type, &carID, &xVehicleLocation, &yVehicleLocation, &direction, &Acceleration);
	road->setRoadName(roadName);

	intersection->setIntersectionID(intersectID);
	intersection->setxCenterPoint(xPosition);
	intersection->setyCenterPoint(yPosition);
	intersection->setNameN(nameN);
	intersection->setNameE(nameE);
	intersection->setNameS(nameS);
	intersection->setNameW(nameW);

	vehicle->setType(type);
	vehicle->setCarID(carID);
	vehicle->setxVehicleLocation(xVehicleLocation);
	vehicle->setyVehicleLocation(yVehicleLocation);
	vehicle->setDirection(direction);
	vehicle->setAcceleration(Acceleration);

	cout << "Road: " << road->getRoadName() << endl;
	cout << "Intersection: " << intersection->getIntersectionID() << endl;
	cout << "Vehicle: " << vehicle->getType() << endl;
	cout << "Road to the North: " << intersection->getNameN() << endl;
	cout << "Road to the East: " << intersection->getNameE() << endl;
	cout << "Road to the South: " << intersection->getNameS() << endl;
	cout << "Road to the West: " << intersection->getNameW() << endl;

	double Direction = vehicle->getDirection();
	double X = vehicle->getxVehicleLocation();
	double Y = vehicle->getyVehicleLocation();

	intersection = map->getNextIntersection(X, Y, Direction, road);

	cout << "Next Intersection: " << intersection->getIntersectionID() << endl;
	cout << "Road to the North: " << intersection->getNameN() << endl;
	cout << "Road to the East: " << intersection->getNameE() << endl;
	cout << "Road to the South: " << intersection->getNameS() << endl;
	cout << "Road to the West: " << intersection->getNameW() << endl;

	cout << (intersection->getNameE() == " ") << endl;

	cin.ignore();
	cout << "Press Enter to end the program." << endl;
	cin.get();

	return 0;
}
