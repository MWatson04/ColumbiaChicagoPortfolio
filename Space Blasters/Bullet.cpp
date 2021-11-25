#include "Bullet.h"


// Constructor & Destructor
Bullet::Bullet()
{
	movementSpeed = 0.f;
}

Bullet::Bullet(sf::Texture* bullet_Texture, float pos_X, float pos_Y, float dir_X, float dir_Y, float movement_Speed)
{
	// Set bullet texture
	bulletSprite.setTexture(*bullet_Texture);

	bulletSprite.setScale(0.9f, 0.6f);
	bulletSprite.setPosition(pos_X, pos_Y);
	direction.x = dir_X;
	direction.y = dir_Y;
	movementSpeed = movement_Speed;
}

Bullet::~Bullet()
{

}

// Accessors
const sf::FloatRect Bullet::GetGlobalBounds() const
{
	return bulletSprite.getGlobalBounds();
}

// Public Functions
void Bullet::Update()
{
	bulletSprite.move(movementSpeed * direction);
}

void Bullet::Render(sf::RenderTarget* target)
{
	target->draw(bulletSprite);
}
