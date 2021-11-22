#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class HealthPack
{
private:
	sf::Sprite healthPackSprite;

public:
	// Constructor & Destructor
	HealthPack();
	HealthPack(sf::Texture* health_Pack_Texture, float pos_X, float pos_Y);
	~HealthPack();

	// Accessors
	const sf::FloatRect GetGlobalBounds() const;

	// Public Functions
	void Update();
	void Render(sf::RenderTarget* target);
};

