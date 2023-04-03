#include "Mesh.h"

Mesh::Mesh(sf::Vector2f startingPos, sf::Vector2f endingPos) : lines(sf::Lines)
{
	updateMesh(startingPos,endingPos);
}

void Mesh::updateMesh(sf::Vector2f startingPos, sf::Vector2f endingPos)
{
	lines.clear();
	sf::Vertex line[2];
	sf::Vector2f start = startingPos;
	while (static_cast<int>(start.x) % 2 != 0)
	{
		start.x++;
	}
	start.x = static_cast<float>((int)start.x);
	while (start.x < endingPos.x)
	{
		line[0] = sf::Vertex(sf::Vector2f(start.x, start.y), sf::Color::White);
		line[1] = sf::Vertex(sf::Vector2f(start.x, endingPos.y), sf::Color::White);

		lines.append(line[0]);
		lines.append(line[1]);
		start.x += 2.f;
	}
	
	start = startingPos;
	while (static_cast<int>(start.y) % 2 != 0)
	{
		start.y++;
	}
	start.y = static_cast<float>((int)start.y);
	while (start.y < endingPos.y)
	{
		line[0] = sf::Vertex(sf::Vector2f(start.x, start.y), sf::Color::White);
		line[1] = sf::Vertex(sf::Vector2f(endingPos.x, start.y), sf::Color::White);

		lines.append(line[0]);
		lines.append(line[1]);
		start.y += 2.f;
	}
}

void Mesh::draw(sf::RenderTarget& target)
{
	target.draw(lines);
}
