#include <iostream>
#include "GameOfLife.h"
#include "LangtonAnt.h"
#include "Simulation.h"
#include <iostream>

int main()
{
	Simulation sim;
	GameOfLife game;
	//LangtonAnt ant;
	sim.setSimulation(&game);
	sim.startSimulation();

	return 0;
}