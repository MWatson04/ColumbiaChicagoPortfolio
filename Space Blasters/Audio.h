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

	// Background music
	sf::Music backgroundMusic;
	sf::Music gameOverMusic;

	// Sound effects
	sf::Sound gunshotSound;
	sf::Sound healthPickupSound;
	sf::Sound gameOverSound;
	sf::Sound enemyDeathSound;
};

