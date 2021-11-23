#pragma once

#include <iostream>

#include <SFML/Audio.hpp>


class Audio
{
private:
	sf::SoundBuffer gunshotBuffer;
	sf::SoundBuffer healthPickupBuffer;
	sf::SoundBuffer enemyDeathBuffer;
	sf::SoundBuffer gameOverBuffer;

	// Private functions
	void InitializeMusic();
	void InitializeSounds();

public:
	// Constructor & Destructor
	Audio();
	~Audio();

	// Public sounds/music to play outside of class
	sf::Music backgroundMusic;
	sf::Music gameOverMusic;

	sf::Sound gunshotSound;
	sf::Sound healthPickupSound;
	sf::Sound gameOverSound;
	sf::Sound enemyDeathSound;
};

