#include "HealthPack.h"


// Constructor & Destrcutor
HealthPack::HealthPack()
{

}

HealthPack::HealthPack(sf::Texture* health_Pack_Texture, float pos_X, float pos_Y)
{
	// Set health pack texture
	healthPackSprite.setTexture(*health_Pack_Texture);

	healthPackSprite.setScale(0.1f, 0.1f);
	healthPackSprite.setPosition(pos_X, pos_Y);
}

HealthPack::~HealthPack()
{

}

// Accessors
const sf::FloatRect HealthPack::GetGlobalBounds() const
{
	return healthPackSprite.getGlobalBounds();
}

const sf::Vector2f& HealthPack::GetPosition() const
{
	return healthPackSprite.getPosition();
}

void HealthPack::SetPosition(float pos_X, float pos_Y)
{
	healthPackSprite.setPosition(pos_X, pos_Y);
}

// Public functions
void HealthPack::Update()
{

}

void HealthPack::Render(sf::RenderTarget* target)
{
	target->draw(healthPackSprite);
}
