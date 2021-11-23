#include "Audio.h"


// Private functions
void Audio::InitializeMusic()
{
	if (!backgroundMusic.openFromFile("Audio/backgroundmusic.ogg"))
		std::cout << "ERROR::AUDIO::MUSIC::BACKGROUNDMUSIC.OGG COULD NOT LOAD" << std::endl;

	backgroundMusic.setLoop(true);
}

void Audio::InitializeSounds()
{
	// Set sound buffers
	if (!gunshotBuffer.loadFromFile("Audio/gunshot2.wav"))
		std::cout << "ERROR::AUDIO::SOUND::GUNSHOT1.WAV COULD NOT LOAD" << std::endl;

	if (!healthPickupBuffer.loadFromFile("Audio/healthpickup.wav"))
		std::cout << "ERROR::AUDIO::SOUND::HEALTHPICKUP.WAV COULD NOT LOAD" << std::endl;

	if (!enemyDeathBuffer.loadFromFile("Audio/enemydeathsound1.wav"))
		std::cout << "ERROR::AUDIO::SOUND::ENEMYDEATHSOUND1.WAV COULD NOT LOAD" << std::endl;

	if (!gameOverBuffer.loadFromFile("Audio/gameoversound.wav"))
		std::cout << "ERROR::AUDIO::SOUND::GAMEOVERSOUND.WAV COULD NOT LOAD" << std::endl;

	// Set buffers to sound variable
	gunshotSound.setBuffer(gunshotBuffer);
	gunshotSound.setVolume(10.f);
	healthPickupSound.setBuffer(healthPickupBuffer);
	enemyDeathSound.setBuffer(enemyDeathBuffer);
	enemyDeathSound.setVolume(20.f);
	gameOverSound.setBuffer(gameOverBuffer);
}

// Constructor & Destructor
Audio::Audio()
{
	InitializeMusic();
	InitializeSounds();
}

Audio::~Audio()
{

}
