#pragma once

#include <SFML/Graphics.hpp>


class Enemy
{
private:
	sf::CircleShape enemyShape;
	int type;
	float movementSpeed;
	
	int damage;

	// Private Functions
	void InitializeEnemy();
	void InitializeVariables();

public:
	// Constructor & Destructor
	Enemy(float pos_X, float pos_Y);
	virtual ~Enemy();

	// Accessors
	const sf::Vector2f& GetPosition() const;
	const sf::FloatRect GetGlobalBounds() const;

	// Public Functions
	void Update();
	void Render(sf::RenderTarget* target);
};

