#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Player
{
private:
	// Set player sprite & texture
	sf::Sprite playerSprite;
	sf::Texture playerTexture;

	float movementSpeed;
	
	float timeSinceLastAttack;
	float attackCooldown;

	int points;
	int currentHealth;
	int maxHealth;

	// Private Functions
	void InitializeVariables();
	void InitializePlayerTexture();
	void InitializePlayerSprite();

public:
	// Constructor & Destructor
	Player();
	virtual ~Player();

	// Accessors
	const sf::Vector2f& GetPosition() const;
	const sf::FloatRect GetGlobalBounds() const;
	const int& GetPoints(int added_Points);
	const int& GetCurrentHealth(int health_Damage);

	// Public Functions
	void MovePlayer(const float dirX, const float dirY);
	const bool canAttack();

	void UpdateAttackCooldown();
	void Update();
	void Render(sf::RenderTarget* target);
};
