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

	// Load a sprite to display
	sf::Texture sprite_sheet;
	if (!sprite_sheet.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Load a mouse texture to display
	sf::Texture mouse_texture;
	if (!mouse_texture.loadFromFile("assets\\mouse.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Setup a mouse Sprite
	sf::Sprite mouse;
	mouse.setTexture(mouse_texture);
	int setMouse = 0;
	

	
	//Setup mouse AABB
	c2AABB aabb_mouse;
	aabb_mouse.min = c2V(mouse.getPosition().x, mouse.getPosition().y);
	aabb_mouse.max = c2V(mouse.getGlobalBounds().width, mouse.getGlobalBounds().width);
	
	//Setup mouse circle
	c2Circle circle_mouse;
	circle_mouse.p = c2V(mouse.getPosition().x,mouse.getPosition().y);
	circle_mouse.r = 42;
	
	//Setup mouse ray
	c2Ray ray_mouse;
	ray_mouse.d = c2Norm(c2V(mouse.getPosition().x, mouse.getPosition().y));
	ray_mouse.p = c2V(mouse.getPosition().x, mouse.getPosition().y);
	ray_mouse.t = c2Len(c2V(mouse.getPosition().x, mouse.getPosition().y));
	
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
	circleAnimated_sprite.setPosition(758, 42);

	circleAnimated_sprite.addFrame(sf::IntRect(3, 88, 84, 84));
	circleAnimated_sprite.addFrame(sf::IntRect(88, 88, 84, 84));
	circleAnimated_sprite.addFrame(sf::IntRect(173, 88, 84, 84));
	circleAnimated_sprite.addFrame(sf::IntRect(258, 88, 84, 84));
	circleAnimated_sprite.addFrame(sf::IntRect(343, 88, 84, 84));
	circleAnimated_sprite.addFrame(sf::IntRect(428, 88, 84, 84));

	//Capsule
	AnimatedSprite capsuleAnimated_sprite(sprite_sheet);
	capsuleAnimated_sprite.setPosition(400, 400);

	capsuleAnimated_sprite.addFrame(sf::IntRect(3, 173, 84, 84));
	capsuleAnimated_sprite.addFrame(sf::IntRect(88, 173, 84, 84));
	capsuleAnimated_sprite.addFrame(sf::IntRect(173, 173, 84, 84));
	capsuleAnimated_sprite.addFrame(sf::IntRect(258, 173, 84, 84));
	capsuleAnimated_sprite.addFrame(sf::IntRect(343, 173, 84, 84));
	capsuleAnimated_sprite.addFrame(sf::IntRect(428, 173, 84, 84));
	

	// Setup Players AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y);
	aabb_player.max = c2V(animated_sprite.getGlobalBounds().width / animated_sprite.getFrames().size(), 
		animated_sprite.getGlobalBounds().height / animated_sprite.getFrames().size());

	//Setup Players Capsule
	c2Capsule capsule_player;
	capsule_player.a = c2V(capsuleAnimated_sprite.getPosition().x, capsuleAnimated_sprite.getPosition().y);
	capsule_player.b = c2V(capsuleAnimated_sprite.getPosition().x, capsuleAnimated_sprite.getPosition().y);
	capsule_player.r = 5.0f;
	

	//Setup Players Poly
	c2Poly poly_player;
	poly_player.count = 5;
	poly_player.norms;
	poly_player.verts;


	//Setup Players Circle
	c2Circle circle_player;
	circle_player.p = c2V(circleAnimated_sprite.getPosition().x, circleAnimated_sprite.getPosition().y);
	circle_player.r = 42.0f;
	circleAnimated_sprite.setOrigin(circle_player.r,circle_player.r);

	//Setup Players Ray
	c2Ray ray_player;
	ray_player.d = c2Norm(c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y));
	ray_player.p = c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y);
	ray_player.t = c2Len(c2V(animated_sprite.getPosition().x, animated_sprite.getPosition().y));

	// Setup the Player
	Player aabb(animated_sprite);
	Player circle(circleAnimated_sprite);
	Player capsule(capsuleAnimated_sprite);


	Input input;

	// Collision result

	//AABB Mouse collisions
	int result = 0;
	int result1 = 0;
	int result2 = 0;
	
	//Circle Mouse collisions
	int result3 = 0;
	int result4 = 0;
	int result5 = 0;
	int result6 = 0;
	int result7 = 0;
	
	//Ray Mouse collisions
	int result8 = 0;
	int result9 = 0;
	int result10 = 0;
	int result11 = 0;
	
	
	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		mouse.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		
		// Update mouse AABB
		aabb_mouse.min = c2V(mouse.getPosition().x, mouse.getPosition().y);
		aabb_mouse.max = c2V(mouse.getGlobalBounds().width, mouse.getGlobalBounds().width);

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
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					
				}
				break;
			default:
				break;
			}
		}

		// Handle input to Player
		aabb.handleInput(input);
		circle.handleInput(input);
		capsule.handleInput(input);

		// Update the Player
		aabb.update();
		circle.update();
		capsule.update();

		// Check for collisions
		//AABB Mouse to AABB Player
		result = c2AABBtoAABB(aabb_mouse, aabb_player);
		cout << ((result != 0) ? ("Collision") : "") << endl;
		if (result){
			aabb.getAnimatedSprite().setColor(sf::Color(255,0,0));
		}
		else {
			aabb.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		}
		//AABB Mouse to Capsule Player
		result1 = c2AABBtoCapsule(aabb_mouse, capsule_player);
		cout << ((result1 != 0) ? ("Collision") : "") << endl;
		if (result1) {
			aabb.getAnimatedSprite().setColor(sf::Color(255, 0, 0));
		}
		else {
			aabb.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		}
		


		////Circle Mouse to AABB Player
		//result3 = c2CircletoAABB(circle_mouse, aabb_player);
		//cout << ((result3 != 0) ? ("Collision") : "") << endl;
		//if (result3) {
		//	aabb.getAnimatedSprite().setColor(sf::Color(255, 0, 0));
		//}
		//else {
		//	aabb.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		//}

		////Ray Mouse to AABB Player
		//result8 = c2RaytoAABB(ray_mouse, aabb_player);
		//cout << ((result3 != 0) ? ("Collision") : "") << endl;
		//if (result3) {
		//	aabb.getAnimatedSprite().setColor(sf::Color(255, 0, 0));
		//}
		//else {
		//	aabb.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		//}







		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		window.draw(aabb.getAnimatedSprite());
		window.draw(circle.getAnimatedSprite());
		window.draw(capsule.getAnimatedSprite());

		window.draw(mouse);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};