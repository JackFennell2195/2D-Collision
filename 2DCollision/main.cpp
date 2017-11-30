#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <Player.h>
#include <Input.h>
#include <Debug.h>
#include <string.h>

using namespace std;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	int currentPlayer = 0;
	int currentMouse = 0;

	// Load a sprite to display
	sf::Texture sprite_sheet;
	if (!sprite_sheet.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Load a mouse texture to display
	sf::Texture AABBMouse_texture;
	if (!AABBMouse_texture.loadFromFile("assets\\AABBMouse.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	sf::Texture CircleMouse_texture;
	if (!CircleMouse_texture.loadFromFile("assets\\CircleMouse.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	sf::Texture RayMouse_texture;
	if (!RayMouse_texture.loadFromFile("assets\\RayMouse.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Setup a mouse Sprite
	sf::Sprite AABBMouse;
	sf::Sprite CircleMouse;
	sf::Sprite RayMouse;

	AABBMouse.setTexture(AABBMouse_texture);
	CircleMouse.setTexture(CircleMouse_texture);
	RayMouse.setTexture(RayMouse_texture);

	int setMouse = 0;
	

	
	//Set up Mouse

	//AABB
	c2AABB aabb_mouse;
	aabb_mouse.min = c2V(AABBMouse.getPosition().x, AABBMouse.getPosition().y);
	aabb_mouse.max = c2V(AABBMouse.getGlobalBounds().width/6, AABBMouse.getGlobalBounds().width/6);
	
	//Circle
	c2Circle circle_mouse;
	circle_mouse.p = c2V(CircleMouse.getPosition().x, CircleMouse.getPosition().y);
	circle_mouse.r = 42;
	
	//Ray
	c2Ray ray_mouse;
	ray_mouse.d = c2Norm(c2V(RayMouse.getPosition().x, RayMouse.getPosition().y));
	ray_mouse.p = c2V(RayMouse.getPosition().x, RayMouse.getPosition().y);
	ray_mouse.t = c2Len(c2V(RayMouse.getPosition().x, RayMouse.getPosition().y));
	


	// Setup Players Default Animated Sprite
	
	//AABB
	AnimatedSprite animated_sprite(sprite_sheet);
	animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	//Circle
	AnimatedSprite circleAnimated_sprite(sprite_sheet);
	circleAnimated_sprite.addFrame(sf::IntRect(3, 343, 84, 84));
	circleAnimated_sprite.addFrame(sf::IntRect(88, 343, 84, 84));
	circleAnimated_sprite.addFrame(sf::IntRect(173, 343, 84, 84));
	circleAnimated_sprite.addFrame(sf::IntRect(258, 343, 84, 84));
	circleAnimated_sprite.addFrame(sf::IntRect(343, 343, 84, 84));
	circleAnimated_sprite.addFrame(sf::IntRect(428, 343, 84, 84));

	//Capsule
	AnimatedSprite capsuleAnimated_sprite(sprite_sheet);
	capsuleAnimated_sprite.addFrame(sf::IntRect(3, 88, 84, 84));
	capsuleAnimated_sprite.addFrame(sf::IntRect(88, 88, 84, 84));
	capsuleAnimated_sprite.addFrame(sf::IntRect(173, 88, 84, 84));
	capsuleAnimated_sprite.addFrame(sf::IntRect(258, 88, 84, 84));
	capsuleAnimated_sprite.addFrame(sf::IntRect(343, 88, 84, 84));
	capsuleAnimated_sprite.addFrame(sf::IntRect(428, 88, 84, 84));
	
	//Polygon
	AnimatedSprite polyAnimated_sprite(sprite_sheet);
	polyAnimated_sprite.addFrame(sf::IntRect(3, 173, 84, 84));
	polyAnimated_sprite.addFrame(sf::IntRect(88, 173, 84, 84));
	polyAnimated_sprite.addFrame(sf::IntRect(173, 173, 84, 84));
	polyAnimated_sprite.addFrame(sf::IntRect(258, 173, 84, 84));
	polyAnimated_sprite.addFrame(sf::IntRect(343, 173, 84, 84));
	polyAnimated_sprite.addFrame(sf::IntRect(428, 173, 84, 84));

	//Ray
	AnimatedSprite rayAnimated_sprite(sprite_sheet);
	rayAnimated_sprite.addFrame(sf::IntRect(3, 258, 84, 84));
	rayAnimated_sprite.addFrame(sf::IntRect(88, 258, 84, 84));
	rayAnimated_sprite.addFrame(sf::IntRect(173, 258, 84, 84));
	rayAnimated_sprite.addFrame(sf::IntRect(258, 258, 84, 84));
	rayAnimated_sprite.addFrame(sf::IntRect(343, 258, 84, 84));
	rayAnimated_sprite.addFrame(sf::IntRect(428, 258, 84, 84));


	//Setup Players

	//AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y);
	aabb_player.max = c2V(animated_sprite.getGlobalBounds().width / animated_sprite.getFrames().size(), 
		animated_sprite.getGlobalBounds().height / animated_sprite.getFrames().size());

	//Capsule
	c2Capsule capsule_player;
	capsule_player.a = c2V(capsuleAnimated_sprite.getPosition().x + 8, capsuleAnimated_sprite.getPosition().y + 21);
	capsule_player.b = c2V(capsuleAnimated_sprite.getPosition().x + 55, capsuleAnimated_sprite.getPosition().y + 21);
	capsule_player.r = 21.0f;
	

	//Poly
	c2Poly poly_player;
	poly_player.count = 4;
	poly_player.norms;
	poly_player.verts[0] = { 20 };
	poly_player.verts[1] = { 20 };
	poly_player.verts[2] = { 20 };
	poly_player.verts[3] = { 20 };

	//Circle
	c2Circle circle_player;
	circle_player.p = c2V(circleAnimated_sprite.getPosition().x+42, circleAnimated_sprite.getPosition().y+42);
	circle_player.r = 42.0f;
	

	//Ray
	c2Ray ray_player;
	ray_player.d = c2Norm(c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y));
	ray_player.p = c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y);
	ray_player.t = c2Len(c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y));


	// Setup the Player
	Player aabb(animated_sprite);
	Player circle(circleAnimated_sprite);
	Player capsule(capsuleAnimated_sprite);
	Player ray(rayAnimated_sprite);
	Player poly(polyAnimated_sprite);


	Input input;

	// Collision result
	int result = 0;
	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		AABBMouse.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		CircleMouse.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		RayMouse.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		// Update mouse AABB
		aabb_mouse.min = c2V(AABBMouse.getPosition().x, AABBMouse.getPosition().y);
		aabb_mouse.max = c2V(AABBMouse.getGlobalBounds().width, AABBMouse.getGlobalBounds().width);

		//Update mouse Circle
		circle_mouse.p = c2V(AABBMouse.getPosition().x + 42, AABBMouse.getPosition().y + 42);
		circle_mouse.r = 42.0f;
		

		ray_mouse;
		ray_mouse;
		ray_mouse;

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					if(currentPlayer>= 0 && currentPlayer<4)
					{
						currentPlayer++;
					}
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					if (currentPlayer > 0 && currentPlayer<=4)
					{
						currentPlayer--;
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					if (currentMouse >= 0 && currentMouse < 2)
					{
						currentMouse++;
					}

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					if (currentMouse > 0 && currentMouse <= 2)
					{
						currentMouse--;
					}
				}
				break;
			default:
				break;
			}
		}
		
		//AABB Mouse to AABB Player
		if (currentPlayer == 0 && currentMouse == 0)
		{
			result = c2AABBtoAABB(aabb_mouse, aabb_player);
		}

		//AABB Mouse to Capsule Player
		else if (currentPlayer == 1 && currentMouse == 0)
		{
			result = c2AABBtoCapsule(aabb_mouse, capsule_player);
		}

		//AABB Mouse to Poly Player
		else if (currentPlayer == 2 && currentMouse == 0)
		{
			//result = c2AABBtoPoly(aabb_mouse, poly_player, );
		}

		//AABB Mouse to Ray Player
		else if (currentPlayer == 3 && currentMouse == 0)
		{
			//result =c2RaytoAABB();
		}

		//Circle Mouse to AABB Player
		else if (currentPlayer == 0 && currentMouse == 1)
		{
			result = c2CircletoAABB(circle_mouse, aabb_player);
		}

		//Circle Mouse to Capsule Player
		else if (currentPlayer == 1 && currentMouse == 1)
		{
			result;
		}

		//Circle Mouse to Poly Player
		else if (currentPlayer == 2 && currentMouse == 1)
		{
			result;
		}

		//Circle Mouse to Ray Player
		else if (currentPlayer == 3 && currentMouse == 1)
		{
			result;
		}

		//Circle Mouse to Circle Player
		else if (currentPlayer == 4 && currentMouse == 1)
		{
			result;
		}

		//Ray Mouse to AABB Player
		else if (currentPlayer == 0 && currentMouse == 2)
		{
			result;
		}

		//Ray Mouse to Capsule Player
		else if (currentPlayer == 1 && currentMouse == 2)
		{
			result;
		}

		//Ray Mouse to Poly Player
		else if (currentPlayer == 2 && currentMouse == 2)
		{
			result;
		}

		//Ray Mouse to Circle Player
		else if (currentPlayer == 4 && currentMouse == 2)
		{
			result;
		}


		// Update the Player
		aabb.update();
		circle.update();
		capsule.update();
		ray.update();
		poly.update();


		// Check for collisions

		//AABB Mouse to AABB Player
		//cout << ((result != 0) ? ("Collision") : "") << endl;
		cout << ((result != 0) ? ("Collision") : "") << endl;
		if (result){
			aabb.getAnimatedSprite().setColor(sf::Color(255,0,0));
		}
		else {
			aabb.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		}

		// Clear screen
		window.clear();
		//Draw the Mouse Current Animated Sprite
		if (currentMouse == 0)
		{
			
			window.draw(AABBMouse);
		}
		else if (currentMouse == 1)
		{
			
			window.draw(CircleMouse);
		}
		else if (currentMouse == 2)
		{
			
			window.draw(RayMouse);
		}

		// Draw the Players Current Animated Sprite
		if (currentPlayer==0)
		{
			window.draw(aabb.getAnimatedSprite());
		}
		else if (currentPlayer == 1)
		{
			window.draw(capsule.getAnimatedSprite());
		}
		else if (currentPlayer == 2)
		{
			window.draw(poly.getAnimatedSprite());
		}
		else if (currentPlayer == 3)
		{
			window.draw(ray.getAnimatedSprite());
		}
		else if (currentPlayer == 4)
		{
			window.draw(circle.getAnimatedSprite());
		}

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};