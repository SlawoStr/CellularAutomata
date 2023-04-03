#include "GameOfLife.h"
#include <chrono>
#include <iostream>
#include "Algo.h"


GameOfLife::GameOfLife() : MovingWindow(sf::Vector2u(1920, 1080), "Simulation", sf::Style::Default, 1000),mesh(getViewBox().first, getViewBox().second)
{

}

void GameOfLife::run()
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

void GameOfLife::update()
{
	std::unordered_map<std::pair<int, int>, std::pair<bool,int>,pair_hash> neighborsCount;
	for (int i = 0; i < cellsVec.size(); i++)
	{
		auto pos = std::make_pair(cellsVec[i].x, cellsVec[i].y);
		neighborsCount[pos].first = true;
		for (int k = -1; k <= 1; ++k)
		{
			for (int n = -1; n <= 1; ++n)
			{
				if (k == 0 && n == 0)
					continue;
				neighborsCount[std::make_pair(cellsVec[i].x + k, cellsVec[i].y + n)].second++;
			}
		}
	}
	cellsVec.clear();
	transform_if(neighborsCount.begin(), neighborsCount.end(), std::back_inserter(cellsVec),
		[](const auto& keyPair) {if (!keyPair.second.first && keyPair.second.second == 3)
									return true;
								else if (keyPair.second.first && (keyPair.second.second == 3 || keyPair.second.second == 2))
									return true;
								return false; },
		[](const auto& keyPair) {return sf::Vector2i(keyPair.first.first,keyPair.first.second); });
}

void GameOfLife::draw()
{
	mesh.draw(window);

	sf::VertexArray quads(sf::Quads, cellsVec.size() * 4);
	sf::Vector2f cellPosition;
	for (int i = 0; i < cellsVec.size(); i++)
	{
		cellPosition = sf::Vector2f(cellsVec[i].x * 2.f,cellsVec[i].y * 2.f);
		sf::Vertex* quad = &quads[i * 4];
		quad[0].position = sf::Vector2f(cellPosition.x,cellPosition.y);
		quad[1].position = sf::Vector2f(cellPosition.x + 2.0f,cellPosition.y);
		quad[2].position = sf::Vector2f(cellPosition.x + 2.0f,cellPosition.y + 2.0f);
		quad[3].position = sf::Vector2f(cellPosition.x,cellPosition.y + 2.0f);

		quad[0].color = sf::Color::Yellow;
		quad[1].color = sf::Color::Yellow;
		quad[2].color = sf::Color::Yellow;
		quad[3].color = sf::Color::Yellow;
	}
	window.draw(quads);
}

void GameOfLife::pollEvent()
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
				spawning = true;
			}
			else if (e.key.code == sf::Mouse::Right)
			{
				killCell(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			}
		}
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::P)
			{
				pause = !pause;
			}
		}
		if (e.type == sf::Event::MouseButtonReleased)
		{
			if (e.key.code == sf::Mouse::Left)
			{
				spawning = false;
			}
		}
	}
	if (spawning)
	{
		addCell(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	}
}

void GameOfLife::addCell(sf::Vector2f mousePos)
{
	sf::Vector2i mouseClick{ static_cast<int>(std::floor(mousePos.x / 2.f)),static_cast<int>(std::floor(mousePos.y / 2.f))};
	// If not found add new element to vector
	if (std::find(cellsVec.begin(), cellsVec.end(), mouseClick) == cellsVec.end())
	{
		cellsVec.push_back(mouseClick);
	}
}

void GameOfLife::killCell(sf::Vector2f mousePos)
{
	sf::Vector2i mouseClick{ static_cast<int>(std::floor(mousePos.x / 2.f)),static_cast<int>(std::floor(mousePos.y / 2.f)) };
	auto it = std::find(cellsVec.begin(), cellsVec.end(), mouseClick);
	if (it != cellsVec.end())
	{
		cellsVec.erase(it);
	}
}