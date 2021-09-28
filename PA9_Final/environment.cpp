#include "Environment.h"
//#include "whatever the tank header is called"

Environment::Environment()
{
	// Generate height of each rectangle
	for (int i = 0; i < NUM_OF_RECT; ++i)
	{
		if (i != 0)
			world[i].setSize(sf::Vector2f(1600 / NUM_OF_RECT, genHeight(world[i - 1].getSize().y)));
		else
			world[i].setSize(sf::Vector2f(1600 / NUM_OF_RECT, genHeight(900 / 2)));

		// the collision algorithm works based off comparing orgigins and sizes between the 2 objects, so i had to adjust the world
		// according to their origins (the dead center of the object)
		world[i].setOrigin(world[i].getSize() / 2.0f);
		// moved this up from the draw function, as we only need to set this once, not every frame
		// also added the halfsize at the end because of the origin change
		world[i].setPosition(sf::Vector2f((1600 / NUM_OF_RECT) * i, 900 - world[i].getSize().y) + (world[i].getSize() / 2.0f));
		sf::Color dark_green(0, 141, 30);
		world[i].setFillColor(dark_green);

	}
}

// generates a random height between 0 and the allowed difference based on the previous slice
int Environment::genHeight(int prevY)
{
	int r = 0;
	do {
		r = rand() % 500 + 250;
	} while (r + DIFF_ALLOWED < prevY || r - DIFF_ALLOWED > prevY); // make sure the next rectangle is 
											  // within a certain height of the previous
	return r;
}

// draws each slice of world
void Environment::drawWorld(sf::RenderWindow& win)
{
	for (int i = 0; i < NUM_OF_RECT; ++i)
	{
		win.draw(world[i]);
	}
}

// returns a collider object for the passed in integer coordinate
Collider Environment::getCollider(int x)
{
	return Collider(world[x]);
}

int Environment::getNumOfRect()
{
	return NUM_OF_RECT;
}

int Environment::getWidthOfRect()
{
	return WIDTH;
}
