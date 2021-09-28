#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include <iostream>

class Projectile
{
protected:
	float impact;
	bool isAirborne;
	int damage;
	double gravity;

	sf::RectangleShape projectile;
	sf::Vector2f projectile_vector;
	sf::Texture projectile_texture;

public:

	//constructor, expects a size to be passed in
	Projectile(sf::Vector2f size, sf::Vector2f vector, sf::Vector2f startingVelocity, float imp)
	{
		projectile.setSize(size);
		impact = imp;
		isAirborne = true;

		projectile.setOrigin(size / 2.0f);
		projectile.setPosition(vector);
		projectile_vector = startingVelocity;
	}

	virtual void setCharacteristics() = 0;

	Collider getCollider()
	{
		return Collider(projectile);
	}

	sf::Vector2f getPosition()
	{
		return projectile.getPosition();
	}

	void setAirborne(bool choice)
	{
		isAirborne = choice;
	}

	void update()
	{
		projectile_vector.y += gravity;
		projectile.move(projectile_vector);
		if (projectile.getPosition().x > 1600 || projectile.getPosition().x < 0 || projectile.getPosition().y < -400 || projectile.getPosition().y > 900)
		{
			setAirborne(false);
		}
	}

	float getImpact()
	{
		return impact;
	}

	int getDamage()
	{
		return damage;
	}

	bool getAirborne()
	{
		return isAirborne;
	}
	//displays the projectile
	void draw(sf::RenderWindow& window)
	{
		window.draw(projectile); //displays the projectile to the screen(the RenderWindow class puts the projectile in proper position)
	}
};