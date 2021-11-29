#pragma once

#include <iostream>
#include <sstream>
#include <map>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "HealthPack.h"
#include "Audio.h"


class Game
{
private:
	bool gameOver;
	bool gamePaused;

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	std::vector<HealthPack*> healthPacks;

	// Player instance
	Player* player;

	// Enemies
	float speedTimer;
	float timeWhenSpeedIncreases;
	float enemySpeed;
	float spawnTimer;
	float timeWhenEnemySpawns;
	std::vector<Enemy*> enemies;

	// Font & Text
	sf::Font pixelFont;
	sf::Font openSansFont;
	sf::Text guiText;
	sf::Text gamePausedText;
	sf::Text resumeOrQuitGameText;
	sf::Text gameOverText;
	sf::Text restartGameText;

	// World background
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackgroundSprite;

	// Health bar
	sf::Texture fullHealthBarTexture;
	sf::Sprite fullHealthBarSprite;

	// Audio instance
	Audio audio;

	// Private Functions
	void InitializeVariables();
	void InitializeFonts();
	void InitializeText();
	void InitializeWindow();
	void InitializeWorld();
	void InitializeHealthBar();
	void InitializeTextures();
	void InitializePlayer();
	void InitializeEnemies();
	void InitializeBackgroundMusic();
	void InitializeGameOverMusic();

public:
	// Constructor & Destructor
	Game();
	~Game();
  
	// Getters
	const bool IsRunning() const;
	const bool& GetGameOver() const;
  
	// Public Functions
	void EventPolling();
	
	void UpdatePause();
	void UpdateGamePaused();
	void UpdateInput();
	void UpdateBullets();
	void UpdatePlayer();
	void UpdateEnemies();
	void UpdateHealthBar();
	void UpdateHealthPack();
	void UpdateScoreText();
	void UpdateGameOver();
	void CheckToRestartGame();
	void UpdateMusic();
	void Update();
	
	void RenderWorld(sf::RenderTarget* target);
	void RenderHealthBar(sf::RenderTarget* target);
	void RenderGUIText(sf::RenderTarget* target);
	void Render();

	void Run();
};
