#include "Player.h"


// Private Functions
void Player::InitializeVariables()
{
	movementSpeed = 8.f;
	attackCooldown = 10.f;
	timeSinceLastAttack = attackCooldown;
	points = 0;
	maxHealth = 5;
	currentHealth = maxHealth;
}

void Player::InitializePlayerTexture()
{
	// Get texture for player
	if (!playerTexture.loadFromFile("Textures/ship.png"))
		std::cout << "ERROR::PLAYER::SHIP.PNG COULD NOT LOAD!" << std::endl;
}

void Player::InitializePlayerSprite()
{
	// Assign the texture to the sprite
	playerSprite.setTexture(playerTexture);
	playerSprite.scale(0.1f, 0.1f);
	playerSprite.setPosition(355.f, 450.f);
}

// Constructor & Destructor
Player::Player()
{
	InitializeVariables();
	InitializePlayerTexture();
	InitializePlayerSprite();
}

Player::~Player()
{

}

// Accessors
const sf::Vector2f& Player::GetPosition() const
{
	return playerSprite.getPosition();
}

const sf::FloatRect Player::GetGlobalBounds() const
{
	return playerSprite.getGlobalBounds();
}

const int& Player::GetPoints(int added_Points)
{
	return points += added_Points;
}

const int& Player::GetCurrentHealth(int health_Damage)
{
	if (currentHealth < 0)
		currentHealth = 0;

	return currentHealth -= health_Damage;
}

// Public Functions
void Player::MovePlayer(const float dirX, const float dirY)
{
	playerSprite.move(movementSpeed * dirX, movementSpeed * dirY);
}

const bool Player::canAttack()
{
	// Cooldown for shooting
	if (timeSinceLastAttack >= attackCooldown)
	{
		timeSinceLastAttack = 0.f;
		return true;
	}
	
	return false;
}

void Player::UpdateAttackCooldown()
{
	if (timeSinceLastAttack < attackCooldown)
		timeSinceLastAttack += 0.5f;
}

void Player::Update()
{
	UpdateAttackCooldown();
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(playerSprite);
}
