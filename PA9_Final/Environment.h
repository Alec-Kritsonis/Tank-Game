#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

// VERY IMPORTANT: make sure the NUM_OF_RECT * WIDTH = 1600! both of these numbers are used in finding the correct slice to check for collision
// EX. numRect = 10 and width = 160, or numRect = 800 and width = 2
#define NUM_OF_RECT 20		// the number of rectangles to be put on the screen 
#define DIFF_ALLOWED 40		// height difference allowed in the rng choosing of a number
#define WIDTH 80			// width of the rectangles

class Environment
{
private:

	sf::RectangleShape world[NUM_OF_RECT];
	int genHeight(int prevY);

public:

	Environment();
	void drawWorld(sf::RenderWindow& win);

	Collider getCollider(int x);
	int getNumOfRect();
	int getWidthOfRect();

};


#endif