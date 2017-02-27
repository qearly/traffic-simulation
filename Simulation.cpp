#include "Simulation.h"
#include "TrafficSimDataParser.h"
#include <vector>
using namespace std;

Simulation::Simulation()
{
	


}

Simulation::~Simulation()
{
	
}

void Simulation::initSimulation()
{
	TrafficSimDataParser *dp;
	Map *roadMap = new Map(dp);
	int vCount = dp->getVehicleCount();

	char carType[64];
	int carID;
	double xPosition;
	double yPosition;
	double startDir;
	double acc;

	for (int i = 0; i <= vCount; i++)
	{
		dp->getVehicleData(carType, &carID, &xPosition, &yPosition, &startDir, &acc);
	}
}

void Simulation::runSimulation()
{
	getSimSpeed();
}

void Simulation::PrintReport()
{

}

void Simulation::getSimSpeed()
{
	cout << "This program can run in regular time, 2X, or 5X. Which would you like?" << endl;
	cin >> simSpeed;
}
