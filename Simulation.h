#ifndef SIMULATION_H_
#define SIMULATION_H_


class Simulation
{
  private:
      Vehicle *allVehicles;
      Map *roadMap;

    public:
      Simulation();
      ~Simulation();
      void runSimulation();
      void PrintReport();
};

#endif
