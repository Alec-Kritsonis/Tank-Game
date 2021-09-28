
#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <iostream>

#include "Player.h"
#include "Environment.h"
#include "Projectile.h"
#include "DefaultProjectile.h"
#include "Heavy.h"
#include "Light.h"
#include "Missile.h"
#include "Grape.h"

#define PI 3.14159265

int main()
{
	srand(time(NULL));

	// window 
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Tanks!");
	window.setFramerateLimit(60);

	// get center of the screen and set window to that location
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 800, (sf::VideoMode::getDesktopMode().height / 2) - 475);
	window.setPosition(centerWindow);

	// player1
	sf::Texture red_tank;
	if (!red_tank.loadFromFile("Red_Tank.png"))
		std::cerr << "Image load error\n";
	// player2
	sf::Texture blue_tank;
	if (!blue_tank.loadFromFile("Blue_Tank.png"))
		std::cerr << "Image load error\n";

	Player player1(&red_tank, sf::Vector2f(red_tank.getSize()), sf::Vector2f(100,200), true);
	Player player2(&blue_tank, sf::Vector2f(blue_tank.getSize()), sf::Vector2f(1000, 200), false);

	Environment env;
	sf::Color light_blue(0, 183, 255);

	// the current weapon that is chosen
	sf::Font font;
	if (!font.loadFromFile("corbel.ttf"))
	{
		throw("FONT LOAD FAILED");
	}
	std::string current_weapon_text = "";
	sf::Text current_weapon;
	current_weapon.setFillColor(sf::Color::Black);
	current_weapon.setFont(font);
	current_weapon.setStyle(sf::Text::Bold);
	int weapon = 0;
	current_weapon_text = "Current Weapon: Light Bomb";
	current_weapon.setString(current_weapon_text);
	current_weapon.setPosition(sf::Vector2f(600, 850));

	// shows the instructions screen
	bool instructions_phase = true;
	std::string instruction_text = "\nInstructions: \n\t\tThe goal is to kill the opposing tank with a random weapon provided at the beginning of your turn\n\t\tEach weapon has different attributes\n\t\tThe red arrow indicates whose current turn it is\n\t\tThe numbers above your tank represent the (angle, power) of your shot\n\n\t\t-90 angle is flat on the horizon pointed to the left\n\t\t0 angle is straight up\n\t\t90 angle is flat on the horizon pointed to the right\n\n\t\t0 power wont go anywhere\n\t\t100 power is as hard as you can shoot\n\nControls:\n\t\tWASD to move the tank\n\t\tLeft/Right arrow keys to change the angle\n\t\tUp/Down arrow keys to change the power\n\t\tSpace Bar to fire";
	sf::Text instructions;
	instructions.setFillColor(sf::Color::White);
	instructions.setFont(font);
	instructions.setString(instruction_text);
	instruction_text = "Hold \"I\" to show instructions";
	sf::Text instruction_promt;
	instruction_promt.setFillColor(sf::Color::Black);
	instruction_promt.setFont(font);
	instruction_promt.setString(instruction_text);
	instruction_promt.setPosition(sf::Vector2f(600, 0));
	instruction_promt.setStyle(sf::Text::Bold);

	// game variables
	bool game_over = false;

	// main game loop
	while (window.isOpen())
	{
		// event loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// close window
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if (!game_over)
		{
			// allows user to see instructions
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				window.clear(sf::Color::Black);
				window.draw(instructions);
				window.display();
			}

			// this is the logic for when a projectile is fired. stop updating everything else and only focus on the projectile
			// as theres no reason to change anything until after it hits the ground
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				double y_vector;
				double x_vector;
				double x_scalar = 5;			// traveling 100 pixels a frame would blow the projectile out of existence, 
				double y_scalar = 7;			// so each vector is downsized by a scalar (these can be modified to greatly change
												// how the projectile behaves)
				sf::Vector2f starting_location;

				// depending on which player's turn it is, use their data to calculate the projectile vectors
				// the calculation is based off the degree-value trig of the angle the player wants to shoot,
				// multiplied by the power and decreased by the scalar mentioned above
				// the starting location is 10 pixels above the tank so that it doesnt immeditately hit the ground when it spawns
				if (player1.getActive())
				{
					x_vector = (player1.getPower() * std::sin((player1.getAngle() * PI) / 180.0)) / x_scalar;
					y_vector = (player1.getPower() * std::cos((player1.getAngle() * PI) / 180.0)) / y_scalar * -1;
					starting_location = player1.getPosition();
					starting_location.y -= 20;
				}
				else
				{
					x_vector = (player2.getPower() * std::sin((player2.getAngle() * PI) / 180.0)) / x_scalar;
					y_vector = (player2.getPower() * std::cos((player2.getAngle() * PI) / 180.0)) / y_scalar * -1;
					starting_location = player2.getPosition();
					starting_location.y -= 20;
				}

				// create a new projectile object and pass in the starting location, velocity vector, and impact
				sf::Vector2f projectile_vector(x_vector, y_vector);

				Projectile* projectile = new DefaultProjectile(sf::Vector2f(50, 50), starting_location, projectile_vector, 1);
				sf::Texture projectile_texture;
				switch (weapon)
				{
					// light shot
				case 0:
					if (!projectile_texture.loadFromFile("Light_Bomb.png"))
						std::cerr << "Image load error\n";
					projectile = new Light(sf::Vector2f(projectile_texture.getSize()), starting_location, projectile_vector, &projectile_texture, 0.5);
					break;
					// heavy shot
				case 1:
					if (!projectile_texture.loadFromFile("Heavy_Bomb.png"))
						std::cerr << "Image load error\n";
					projectile = new Heavy(sf::Vector2f(projectile_texture.getSize()), starting_location, projectile_vector, &projectile_texture, 0.0);
					break;
				case 2:
					// missle
					if (!projectile_texture.loadFromFile("Missile.png"))
						std::cerr << "Image load error\n";
					projectile = new Missile(sf::Vector2f(projectile_texture.getSize()), starting_location, projectile_vector, &projectile_texture, 0.5);
					break; 
				case 3:
					// grape
					if (!projectile_texture.loadFromFile("Grape.png"))
						std::cerr << "Image load error\n";
					projectile = new Grape(sf::Vector2f(projectile_texture.getSize()), starting_location, projectile_vector, &projectile_texture, 0.1);
					break;
				}

				// while the projectile is in the air (hasnt collided with anything)
				while (projectile->getAirborne() == true)
				{

					projectile->update();

					// colliders used to find out what it hit
					double current_proj_x = std::ceil(projectile->getPosition().x / env.getWidthOfRect());
					if (env.getCollider(current_proj_x - 1).checkCollision(projectile->getCollider(), projectile->getImpact())) {
						std::cout << "Hit Ground\n";
						projectile->setAirborne(false);
					}
					else if (player1.getActive() == false && player1.getCollider().checkCollision(projectile->getCollider(), 1.0f))
					{
						std::cout << "Hit player 1\n";
						player1.changeHealth(-1 * projectile->getDamage());
						projectile->setAirborne(false);

					}
					else if (player2.getActive() == false && player2.getCollider().checkCollision(projectile->getCollider(), 1.0f))
					{
						std::cout << "Hit player 2\n";
						player2.changeHealth(-1 * projectile->getDamage());
						projectile->setAirborne(false);
					}

					// check for game over
					if (player1.getHealth() <= 0 || player2.getHealth() <= 0)
						game_over = true;

					// renders the window while the projectile is in the air since we are stuck in this loop
					window.clear(light_blue);
					env.drawWorld(window);
					player1.draw(window);
					player2.draw(window);
					projectile->draw(window);
					window.display();
				}


				// swaps who is active/can move and aim
				player1.setActive(!player1.getActive());
				player2.setActive(!player2.getActive());

				// get random weapon
				weapon = rand() % 4;

				// changes the text at the bottom of the screen 
				switch (weapon)
				{
				case 0:
					current_weapon_text = "Current Weapon: Light Bomb";
					break;
				case 1:
					current_weapon_text = "Current Weapon: Heavy Bomb";
					break;
				case 2:
					current_weapon_text = "Current Weapon: Missle";
					break;
				case 3:
					current_weapon_text = "Current Weapon: Grape";
					break;
				}
				current_weapon.setString(current_weapon_text);
			}


			player1.update();
			player2.update();


			// this calculates which element/slice of the world array to compare for colliding, depending on the tank's location
			double p1_current_x_coord = std::ceil(player1.getPosition().x / env.getWidthOfRect());
			// the actual collision check
			env.getCollider(p1_current_x_coord - 1).checkCollision(player1.getCollider(), 1.0f);

			// same for player 2
			double p2_current_x_coord = std::ceil(player2.getPosition().x / env.getWidthOfRect());
			env.getCollider(p2_current_x_coord - 1).checkCollision(player2.getCollider(), 1.0f);

			// render
			window.clear(light_blue);
			env.drawWorld(window);
			player1.draw(window);
			player2.draw(window);
			window.draw(instruction_promt);
			window.draw(current_weapon);
			window.display();
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				window.close();

			window.clear(sf::Color::Black);
			if (player1.getHealth() < 0)
			{
				instruction_promt.setString("Player 2 Wins!");
				instruction_promt.setFillColor(sf::Color::Blue);
			}
			else
			{
				instruction_promt.setString("Player 1 Wins!");
				instruction_promt.setFillColor(sf::Color::Red);
			}
			current_weapon_text = "Press enter to exit...";
			current_weapon.setString(current_weapon_text);
			current_weapon.setFillColor(sf::Color::White);
			instruction_promt.setScale(sf::Vector2f(5, 5));
			instruction_promt.setPosition(400, 300);
			window.draw(instruction_promt);
			window.draw(current_weapon);
			window.display();
		}
	}

	return 0;
}