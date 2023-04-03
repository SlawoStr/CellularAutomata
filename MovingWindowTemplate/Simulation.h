#pragma once
#include "MovingWindow.h"


class Simulation
{
public:
	void setSimulation(MovingWindow* sim);
	void startSimulation();
private:
	MovingWindow* simulation{ nullptr };
};