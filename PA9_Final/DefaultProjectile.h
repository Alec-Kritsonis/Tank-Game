#pragma once
#include "Projectile.h"

class DefaultProjectile : public Projectile
{

public:

	DefaultProjectile(sf::Vector2f size, sf::Vector2f starting_position, sf::Vector2f startingVelocity, int num) : Projectile(size, starting_position, startingVelocity, num)
	{
		projectile.setFillColor(sf::Color::Yellow);
		setCharacteristics();
	}

	void setCharacteristics()
	{
		gravity = 0.15;
		damage = 5;
	}
};

