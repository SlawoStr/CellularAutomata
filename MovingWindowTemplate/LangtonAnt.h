#pragma once
#include <unordered_map>
#include "MovingWindow.h"
#include "Mesh.h"
#include "Ant.h"
#include "Algo.h"
#include "RandomNumberGenerator.h"

class LangtonAnt : public MovingWindow 
{
public:
	LangtonAnt();
	void run() override;
private:
	void update() override;
	void draw() override;
	void pollEvent() override;
	void createAnt(sf::Vector2f mousePos);
	void creatCell(sf::Vector2i position, sf::Color color);
	void resetVertexArray();
	void initializeColorMap();
	COLOR getTransformedColor(COLOR color);
private:
	Mesh mesh;
	std::vector<Ant> ants;
	std::unordered_map<std::pair<int, int>, COLOR ,pair_hash> vertexMap;
	std::unordered_map < COLOR, std::pair<sf::Color, bool>,EnumClassHash> colorMap;
	sf::VertexArray quads;
	bool pause{ true };
	RandomNumberGenerator generator;
};