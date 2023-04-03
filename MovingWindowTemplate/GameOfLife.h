#pragma once
#include "MovingWindow.h"
#include "Mesh.h"
#include <unordered_map>

class GameOfLife : public MovingWindow
{
public:
	GameOfLife();
	void run() override;
private:
	void update() override;
	void draw() override;
	void pollEvent() override;
	void addCell(sf::Vector2f mousePos);
	void killCell(sf::Vector2f mousePos);
private:
	Mesh mesh;
	std::vector<sf::Vector2i> cellsVec;
	bool pause{ true };
	bool spawning{ false };
};