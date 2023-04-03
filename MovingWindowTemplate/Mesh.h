#pragma once
#include "SFML/Graphics.hpp"

class Mesh
{
public:
	Mesh(sf::Vector2f startingPos, sf::Vector2f endingPos);
	void updateMesh(sf::Vector2f startingPos, sf::Vector2f endingPos);
	void draw(sf::RenderTarget& target);
private:
	sf::VertexArray lines;
};