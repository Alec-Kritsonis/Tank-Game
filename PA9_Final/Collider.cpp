#include "Collider.h"

// returns object that is passed in's position
sf::Vector2f Collider::getPosition()
{
	return body.getPosition();
}

// returns the half size which is used for the algorithm/colliding with the center
sf::Vector2f Collider::getHalfSize()
{
	return body.getSize() / 2.0f;
}

// *constructor noises*
Collider::Collider(sf::RectangleShape& body) : body(body)
{

}

// gets called when a collision happens and forces the other object out
void Collider::move(float dx, float dy)
{
	body.move(0, dy);
}

// checks if this object's center has collided with another object's center through an algorithm explained in the video (link in sources.txt)
bool Collider::checkCollision(Collider other, float push)
{
	sf::Vector2f otherPosition = other.getPosition();
	sf::Vector2f otherHalfSize = other.getHalfSize();
	sf::Vector2f thisPosition = getPosition();
	sf::Vector2f thisHalfSize = getHalfSize();

	double x1 = otherPosition.x;
	double x2 = thisPosition.x;
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	// checks the bounding boxes, and if theres a collision, depending on which object is "heavier", pushes it out
	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				move(intersectX * (1.0f - push), 0.0f);
				other.move(-intersectX * push, 0.0f);
				other.move(0.0f, -1);
			}
			else
			{
				move(-intersectX * (1.0f - push), 0.0f);
				other.move(intersectX * push, 0.0f);
				other.move(0.0f, -1);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				move(0.0f, intersectY * (1.0f - push));
				other.move(0.0f, -intersectY * push);
			}
			else
			{
				move(0.0f, -intersectY * (1.0f - push));
				other.move(0.0f, intersectY * push);
			}
		}
		return true;
	}
	return false;
}

