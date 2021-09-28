#pragma once

#include "SFML/Graphics.hpp"
#include "Collider.h"
#include <string>

class Player
{

private:

	sf::RectangleShape body;
	sf::CircleShape *turn_arrow;
	sf::Font font;
	sf::Text aim;
	sf::Text health_text;

	int power;
	int angle;
	double speed;
	double gravity;
	int health;

	bool active;		// if it is this tank's turn to move/aim/shoot. gets changed when spacebar is hit

public:

	Player(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool turn);

	void update();
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition();
	Collider getCollider();

	void setActive(bool x);
	bool getActive();

	double getAngle();
	double getPower();
	int getHealth();
	void changeHealth(int amount);

};

