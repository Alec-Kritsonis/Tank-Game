#pragma once

#include "Projectile.h"

class Light : public Projectile
{

public:
	Light(sf::Vector2f size, sf::Vector2f starting_position, sf::Vector2f startingVelocity, sf::Texture* texture, float imp) : Projectile(size, starting_position, startingVelocity, imp)
	{
		projectile.setTexture(texture);
		setCharacteristics();
	}

	void setCharacteristics()
	{
		gravity = 0.15;
		damage = 10;
	}
};

