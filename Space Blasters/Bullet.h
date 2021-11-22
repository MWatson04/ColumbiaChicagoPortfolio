#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class Bullet
{
private:
	sf::Sprite bulletSprite;
	sf::Vector2f direction;
	
	float movementSpeed;

public:
	// Constructor & Destructor
	Bullet();
	Bullet(sf::Texture* bullet_Texture, float pos_X, float pos_Y, float dir_X, float dir_Y, float movement_Speed);
	~Bullet();

	// Accessors
	const sf::FloatRect GetGlobalBounds() const;

	// Public Functions
	void Update();
	void Render(sf::RenderTarget* target);
};

