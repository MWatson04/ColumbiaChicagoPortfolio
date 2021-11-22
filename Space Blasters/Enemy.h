#pragma once

#include <SFML/Graphics.hpp>


class Enemy
{
private:
	sf::CircleShape enemyShape;
	
	int damage;
	float movementSpeed;

	// Private Functions
	void InitializeEnemy();
	void InitializeVariables();

public:
	// Constructor & Destructor
	Enemy();
	Enemy(float pos_X, float pos_Y, float speed);
	~Enemy();

	// Accessors
	const sf::Vector2f& GetPosition() const;
	const sf::FloatRect GetGlobalBounds() const;

	// Modifier
	void SetPosition(float pos_X, float pos_Y);

	// Public Functions
	void Update();
	void Render(sf::RenderTarget* target);
};
