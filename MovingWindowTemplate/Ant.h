#pragma once
#include "SFML/Graphics.hpp"

enum class Direction : int { UP, RIGHT, DOWN, LEFT };
enum class COLOR :int { WHITE, RED, GREEN, YELLOW, BLUE,PINK,GREY };

class Ant
{
public:
	Ant(sf::Vector2i antPosition, sf::Color color, Direction direction) : antPosition(antPosition), color(color), direction(direction) {}
	// Getters
	sf::Color getColor()const { return color; }
	Direction getDirection()const { return direction; }
	sf::Vector2i getPosition()const { return antPosition; }
	// Setters
	void setPosition(sf::Vector2i pos) { this->antPosition = pos; }
	void setDirection(Direction direction) { this->direction = direction; }
	//Movement
	void turnLeft() { int newDirection = static_cast<int>(direction) - 1;  direction = newDirection < 0 ? Direction::LEFT : static_cast<Direction>(newDirection); };
	void turnRight() { int newDirection = static_cast<int>(direction) + 1; direction = newDirection > 3 ? Direction::UP : static_cast<Direction>(newDirection); };
	void move() { if (direction == Direction::UP)antPosition.y -= 1; else if (direction == Direction::RIGHT)antPosition.x += 1; else if (direction == Direction::DOWN)antPosition.y += 1; else if (direction == Direction::LEFT)antPosition.x -= 1; }
private:
	sf::Color color;
	Direction direction;
	sf::Vector2i antPosition;
};