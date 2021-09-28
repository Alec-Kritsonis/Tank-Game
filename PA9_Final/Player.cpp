#include "Player.h"

// inititalizes the player object
Player::Player(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool turn)
{
	turn_arrow = new sf::CircleShape(15, 3);
	turn_arrow->setFillColor(sf::Color::Red);
	turn_arrow->rotate(180);
	speed = 4;
	gravity = 3;
	angle = 0;
	power = 50;
	active = turn;
	health = 100;

	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);

	// sets up the aim cooridnate string
	if (!font.loadFromFile("corbel.ttf"))
	{
		throw("FONT LOAD FAILED");
	}
	aim.setFont(font);
	aim.setScale(0.75, 0.75);
	aim.setFillColor(sf::Color::Black);

	std::string text = "(" + std::to_string(angle) + ", " + std::to_string(power) + ")";
	aim.setString(text);
	aim.setPosition(body.getPosition().x - 30, body.getPosition().y - 60);

	health_text.setFont(font);
	health_text.setScale(0.75, 0.75);
	health_text.setFillColor(sf::Color::Black);

	text = "Health: " + std::to_string(health);
	health_text.setString(text);
	health_text.setPosition(body.getPosition().x - 45, body.getPosition().y + 30);
}

// gets called each frame and checks for keyboard input. gravity is checked every frame, input is checked only when active
void Player::update()
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (body.getPosition().x - (body.getSize().x / 2)) > 0 && active)
		movement.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (body.getPosition().x + (body.getSize().x / 2)) < 1600 && active)
		movement.x += speed;

	// impractical but for my own sanity when checking collisions
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && active)
		movement.y -= speed * 1.5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && active)
		movement.y += speed;*/

	// arrow keys to change angle/power
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && angle > -90 && active)
		angle -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && angle < 90 && active)
		angle += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && power < 100 && active)
		power += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && power > 0 && active)
		power -= 1;

	// IMPLEMENTS THE GRAVITY FOR THE TANK
	if (body.getPosition().y + (body.getSize().y / 2) < 900)
		movement.y += gravity;
	body.move(movement);

	// updates the text
	std::string text = "(" + std::to_string(angle) + ", " + std::to_string(power) + ")";
	aim.setString(text);
	aim.setPosition(body.getPosition().x - 30, body.getPosition().y - 60);

	text = "Health: " + std::to_string(health);
	health_text.setString(text);
	health_text.setPosition(body.getPosition().x - 45, body.getPosition().y + 30);

	// turn arrow
	turn_arrow->setPosition(body.getPosition().x + 10, body.getPosition().y - 60);
}

// draws the player
void Player::draw(sf::RenderWindow& window)
{
	if (active)
		window.draw(*turn_arrow);
	window.draw(body);
	window.draw(aim);
	window.draw(health_text);
}

// returns the tanks positions (top left corner i believe)
sf::Vector2f Player::getPosition()
{
	return body.getPosition();
}

// returns a collider object for this object
Collider Player::getCollider()
{
	return Collider(body);
}

void Player::setActive(bool x)
{
	active = x;
}

bool Player::getActive()
{
	return active;
}

double Player::getAngle()
{
	return angle;
}

double Player::getPower()
{
	return power;
}

int Player::getHealth()
{
	return health;
}

void Player::changeHealth(int amount)
{
	health += amount;
}
