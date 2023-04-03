#include "Simulation.h"

void Simulation::setSimulation(MovingWindow* sim)
{
	simulation = sim;
}

void Simulation::startSimulation()
{
	if (simulation)
	{
		simulation->run();
	}
}
