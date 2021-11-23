#include "Enemy.h"


// Private Functions
void Enemy::InitializeEnemy()
{
	// Randomize enemy radius, vertex count, and color when spawned
	enemyShape.setRadius(static_cast<float>(rand() % 20 + 20));
	enemyShape.setPointCount(rand() % 3 + 5);
	enemyShape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

void Enemy::InitializeVariables()
{
	movementSpeed = 2.f;
	damage = 1;
}

// Constructor & Destructor
Enemy::Enemy()
{

}

Enemy::Enemy(float pos_X, float pos_Y, float speed)
{
	InitializeVariables();
	InitializeEnemy();
	enemyShape.setPosition(pos_X, pos_Y);
	movementSpeed = speed;
}

Enemy::~Enemy()
{

}

// Accessors
const sf::Vector2f& Enemy::GetPosition() const
{
	return enemyShape.getPosition();
}

const sf::FloatRect Enemy::GetGlobalBounds() const
{
	return enemyShape.getGlobalBounds();
}

// Modifiers
void Enemy::SetPosition(float pos_X, float pos_Y)
{
	enemyShape.setPosition(pos_X, pos_Y);
}

// Public Functions
void Enemy::Update()
{
	enemyShape.move(0.f, movementSpeed);
}

void Enemy::Render(sf::RenderTarget* target)
{
	target->draw(enemyShape);
}
