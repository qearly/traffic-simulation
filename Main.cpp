#include "includes.h"


using namespace std;

int main()
{
	Simulation *sim = new Simulation();

	if (sim->initSimulation())
	{
		sim->runSimulation();
	}

	cin.ignore();
	cout << "Press Enter to exit." << endl;
	cin.get();

	return 0;
}
