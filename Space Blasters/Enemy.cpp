#include "Enemy.h"


// Private Functions
void Enemy::InitializeEnemy()
{
	// Randomize enemy size and shape through its radius and number of vertices
	enemyShape.setRadius(static_cast<float>(rand() % 20 + 25));
	enemyShape.setPointCount(rand() % 3 + 6);
	enemyShape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

// Constructor & Destructor
Enemy::Enemy()
{
	movementSpeed = 0.f;
}

Enemy::Enemy(float pos_X, float pos_Y, float movement_Speed)
{
	InitializeEnemy();
	enemyShape.setPosition(pos_X, pos_Y);
	movementSpeed = movement_Speed;
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
