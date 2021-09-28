#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class Collider
{

private:
	sf::RectangleShape& body;


public:

	Collider(sf::RectangleShape& body);

	void move(float dx, float dy);

	bool checkCollision(Collider other, float push);
	sf::Vector2f getPosition();
	sf::Vector2f getHalfSize();

};

