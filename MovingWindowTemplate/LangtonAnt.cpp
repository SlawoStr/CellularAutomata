#include "LangtonAnt.h"
#include <chrono>
#include <iostream>

LangtonAnt::LangtonAnt() : MovingWindow(sf::Vector2u(1920, 1080), "Simulation", sf::Style::Default, 1000), mesh(getViewBox().first, getViewBox().second),quads(sf::Quads), generator(0,4,0,255)
{
	initializeColorMap();
}

void LangtonAnt::run()
{
	while (window.isOpen())
	{
		auto start = std::chrono::steady_clock::now();
		window.clear(sf::Color::Black);
		draw();
		window.display();
		if (!pause)
		{
			update();
		}
		pollEvent();
		auto end = std::chrono::steady_clock::now();
		std::cout << "Elapsed time in miliseconds: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " ms" << std::endl;
	}
}

void LangtonAnt::update()
{
	for (auto& ant : ants)
	{
		auto it = vertexMap.find(std::make_pair(ant.getPosition().x, ant.getPosition().y));
		COLOR newColor = COLOR::WHITE;
		if (it != vertexMap.end())
		{
			// Find new color and swap it with current cell
			newColor = getTransformedColor((*it).second);
			(*it).second = newColor;
			resetVertexArray();
		}
		else
		{
			creatCell(ant.getPosition(), sf::Color::White);
		}
		// Update ant
		if (colorMap.at(newColor).second)
		{
			ant.turnRight();
		}
		else
		{
			ant.turnLeft();
		}
		ant.move();
	}
}

void LangtonAnt::draw()
{
	window.draw(quads);
	mesh.draw(window);
}

void LangtonAnt::pollEvent()
{
	sf::Event e;

	while (window.pollEvent(e))
	{
		if (handleWindowEvent(e))
		{
			mesh.updateMesh(getViewBox().first, getViewBox().second);
			continue;
		}
		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (e.key.code == sf::Mouse::Left)
			{
				createAnt(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			}
		}
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::P)
			{
				pause = !pause;
			}
		}
	}
}

void LangtonAnt::createAnt(sf::Vector2f mousePos)
{
	sf::Vector2i mouseClick{ static_cast<int>(std::floor(mousePos.x / 2.f)),static_cast<int>(std::floor(mousePos.y / 2.f)) };

	// Check if there is already different ant on that position
	auto vecIt = std::find_if(ants.begin(), ants.end(), [&mouseClick](const auto& ant) {return ant.getPosition() == mouseClick; });
	if (vecIt != ants.end())
		return;
	
	// Create new ant
	ants.emplace_back(mouseClick, sf::Color::Yellow,static_cast<Direction>(generator.getShortDistr()));

	// Check if vertex is already in map
	auto it = vertexMap.find(std::make_pair(mouseClick.x, mouseClick.y));

	if (it!=vertexMap.end())
	{
		(*it).second = COLOR::WHITE;
		resetVertexArray();
	}
	else
	{
		creatCell(mouseClick, sf::Color::White);
	}
}

void LangtonAnt::creatCell(sf::Vector2i position, sf::Color color)
{
	sf::Vector2f cellPosition = sf::Vector2f(position.x * 2.f, position.y * 2.f);

	// Create new quad and add it to vertex array
	sf::Vertex quad[4];
	quad[0].color = color;
	quad[1].color = color;
	quad[2].color = color;
	quad[3].color = color;

	quad[0].position = sf::Vector2f(cellPosition.x, cellPosition.y);
	quad[1].position = sf::Vector2f(cellPosition.x + 2.0f, cellPosition.y);
	quad[2].position = sf::Vector2f(cellPosition.x + 2.0f, cellPosition.y + 2.0f);
	quad[3].position = sf::Vector2f(cellPosition.x, cellPosition.y + 2.0f);

	quads.append(quad[0]);
	quads.append(quad[1]);
	quads.append(quad[2]);
	quads.append(quad[3]);
	
	// Creat new entry in map
	vertexMap.insert(std::make_pair(std::make_pair(position.x, position.y), COLOR::WHITE));
}

void LangtonAnt::resetVertexArray()
{
	quads.clear();

	for (auto it = vertexMap.begin(); it != vertexMap.end(); ++it)
	{
		creatCell(sf::Vector2i{ (*it).first.first,(*it).first.second }, colorMap.at((*it).second).first);
	}
}

void LangtonAnt::initializeColorMap()
{
	// Cells behaviour based on their color false ->left true -> right
	colorMap.insert(std::make_pair(COLOR::WHITE, std::make_pair(sf::Color::White, true)));
	colorMap.insert(std::make_pair(COLOR::RED, std::make_pair(sf::Color::Red, true)));
	colorMap.insert(std::make_pair(COLOR::GREEN, std::make_pair(sf::Color::Green, false)));
	colorMap.insert(std::make_pair(COLOR::YELLOW, std::make_pair(sf::Color::Yellow, false)));
	colorMap.insert(std::make_pair(COLOR::BLUE, std::make_pair(sf::Color::Blue, false)));
	colorMap.insert(std::make_pair(COLOR::PINK, std::make_pair(sf::Color(160,160,160), true)));
	colorMap.insert(std::make_pair(COLOR::GREY, std::make_pair(sf::Color(255, 102, 255), true)));
}

COLOR LangtonAnt::getTransformedColor(COLOR color)
{
	switch (color)
	{
	case COLOR::WHITE:
		return COLOR::RED;
		break;
	case COLOR::RED:
		return COLOR::GREEN;
		break;
	case COLOR::GREEN:
		return COLOR::YELLOW;
		break;
	case COLOR::YELLOW:
		return COLOR::BLUE;
		break;
	case COLOR::BLUE:
		return COLOR::PINK;
		break;
	case COLOR::PINK:
		return COLOR::GREY;
		break;
	case COLOR::GREY:
		return COLOR::WHITE;
		break;
	}
}
