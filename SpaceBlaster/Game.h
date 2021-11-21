#pragma once

#include <iostream>
#include <sstream>
#include <map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


class Game
{
private:
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	
	bool gameOver;

	// Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	// Player instance
	Player* player;

	// Enemies
	float spawnTimer;
	float timeWhenEnemySpawns;
	std::vector<Enemy*> enemies;

	// Font & Text
	sf::Font font;
	sf::Text guiText;
	sf::Text gameOverText;
	sf::Text restartGameText;

	// World background
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackground;
  
	// Private Functions
	void InitializeVariables();
	void InitializeFonts();
	void InitializeText();
	void InitializeWindow();
	void InitializeWorld();
	void InitializeTextures();
	void InitializePlayer();
	void InitializeEnemies();
  
public:
	// Constructor & Destructor
	Game();
	~Game();
  
	// Accessors
	const bool IsRunning() const;
	const bool& GetEndGame() const;
  
	// Public Functions
	void PollEvents();

	void UpdateInput();
	void UpdateBullets();
	void UpdatePlayer();
	void UpdateEnemies();
	void UpdateText();
	void UpdateGameOver();
	void Update();

	void RenderWorld(sf::RenderTarget* target);
	void RenderText(sf::RenderTarget* target);
	void Render();

	void Run();
};
