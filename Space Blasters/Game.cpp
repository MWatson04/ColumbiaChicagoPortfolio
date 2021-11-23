#include "Game.h"


// Private Functions
void Game::InitializeVariables()
{
	gameOver		= false;
	gamePaused		= false;
}

void Game::InitializeFonts()
{
	// Error message if file can't be loaded
	if (!fontOne.loadFromFile("Fonts/Dosis-Light.ttf"))
		std::cout << "ERROR::GAME::FONT::DOSIS-LIGHT.TTF COULD NOT LOAD!" << std::endl;

	// Error message if file can't be loaded
	if (!fontTwo.loadFromFile("Fonts/OpenSans-Regular.ttf"))
		std::cout << "ERROR::GAME::FONT::OPENSANS-REGULAR.TTF COULD NOT LOAD!" << std::endl;
}

void Game::InitializeText()
{
	// Set GUI text
	guiText.setFont(fontOne);
	guiText.setFillColor(sf::Color::White);
	guiText.setPosition(20.f, 15.f);
	guiText.setCharacterSize(32);

	// Set game paused text
	gamePausedText.setFont(fontOne);
	gamePausedText.setFillColor(sf::Color::White);
	gamePausedText.setPosition(275.f, 220.f);
	gamePausedText.setCharacterSize(80);
	gamePausedText.setString("PAUSED");

	// Set text for resuming or quitting game
	resumeOrQuitGameText.setFont(fontTwo);
	resumeOrQuitGameText.setFillColor(sf::Color::White);
	resumeOrQuitGameText.setPosition(275.f, 325.f);
	resumeOrQuitGameText.setCharacterSize(24);
	resumeOrQuitGameText.setString("Press Space to resume\n				  Or\n      Press Q to Quit");

	// Set game over text
	gameOverText.setFont(fontOne);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setPosition(215.f, 230.f);
	gameOverText.setCharacterSize(80);
	gameOverText.setString("GAME OVER");

	// Set restart game text
	restartGameText.setFont(fontOne);
	restartGameText.setFillColor(sf::Color::White);
	restartGameText.setPosition(265.f, 330.f);
	restartGameText.setCharacterSize(32);
	restartGameText.setString("Press Space to Restart");
}

void Game::InitializeWindow()
{
	// Set window variables
	videoMode = sf::VideoMode(800, 600);
	window = new sf::RenderWindow(videoMode, "Game 3", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);
}

void Game::InitializeWorld()
{
	// Error message if file can't be loaded
	if (!worldBackgroundTexture.loadFromFile("Textures/background1.jpg"))
		std::cout << "ERROR::GAME::BACKGROUND1.JPG COULD NOT LOAD!" << std::endl;

	// Set background texture
	worldBackgroundSprite.setTexture(worldBackgroundTexture);
	worldBackgroundSprite.setScale(0.45f, 0.6f);
}

void Game::InitializeHealthBar()
{
	// Error message if file can't be loaded
	if (!fullHealthBarTexture.loadFromFile("Textures/actualhealthbar.png"))
		std::cout << "ERROR::GAME::FULLHEALTHBAR2.PNG COULD NOT LOAD!" << std::endl;

	// Set health bar
	fullHealthBarSprite.setTexture(fullHealthBarTexture);
	fullHealthBarSprite.setPosition(240.f, 560.f);
}

void Game::InitializeTextures()
{
	// Set bullet texture
	textures["BULLET"] = new sf::Texture();
	textures["BULLET"]->loadFromFile("Textures/bullet.png");

	textures["HEALTHPACK"] = new sf::Texture();
	textures["HEALTHPACK"]->loadFromFile("Textures/healthpack.png");
}

void Game::InitializePlayer()
{
	player = new Player();
}

void Game::InitializeEnemies()
{
	// Set timer for enemies speed
	speedTimer = 0.f;
	timeWhenSpeedIncreases = 100.f;
	newSpeed = 2.f;

	// Set timer for enemies spawn rate
	timeWhenEnemySpawns = 30.f;
	spawnTimer = timeWhenEnemySpawns;
}

void Game::InitializeBackgroundMusic()
{
	audio.backgroundMusic.play();
}

// Constructor & Destructor
Game::Game()
{
	// All initilization
	InitializeVariables();
	InitializeFonts();
	InitializeText();
	InitializeWindow();
	InitializeHealthBar();
	InitializeWorld();
	InitializeTextures();
	InitializePlayer();
	InitializeEnemies();
	InitializeBackgroundMusic();
}

Game::~Game()
{
	// Delete memory
	delete window;
	delete player;

	// Delete textures
	for (auto& i : textures)
	{
		delete i.second;
	}

	// Delete bullets
	for (auto* i : bullets)
	{
		delete i;
	}

	// Delete enemies
	for (auto* i : enemies)
	{
		delete i;
	}

	// Delete health packs
	for (auto* i : healthPacks)
	{
		delete i;
	}
}

// Accessors
const bool Game::IsRunning() const
{
	return window->isOpen();
}

const bool& Game::GetGameOver() const
{
	return gameOver;
}

// Public Functions
void Game::PollEvents()
{
	// Event Polling
	while (window->pollEvent(event))
	{
		if (event.Event::type == sf::Event::Closed)
			window->close();
	}
}

void Game::UpdatePause()
{
	// Pause game when escape is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		gamePaused = true;
}

void Game::UpdateGameWhenPaused()
{
	// When game is paused, continue by pressing space or quit by pressing Q
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		gamePaused = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		window->close();
}

void Game::UpdateInput()
{
	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player->MovePlayer(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player->MovePlayer(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player->MovePlayer(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player->MovePlayer(0.f, 1.f);

	// Instantiate Bullet
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->canAttack())
	{
		bullets.push_back(
			new Bullet(textures["BULLET"], 
			player->GetPosition().x + player->GetGlobalBounds().width / 2.f, 
			player->GetPosition().y, 
			0.f, 
			-1.f, 
			15.f)
		);

		audio.gunshotSound.play();
	}
}

void Game::UpdateBullets()
{
	unsigned bullet_Element = 0;

	// Update Bullet
	for (auto* bullet : bullets)
	{
		bullet->Update();

		// Bullet culling (top of screen)
		if (bullet->GetGlobalBounds().top + bullet->GetGlobalBounds().height < 0.5f)
		{
			// Delete bullet
			delete bullets.at(bullet_Element);
			bullets.erase(bullets.begin() + bullet_Element);
			--bullet_Element;
		}

		++bullet_Element;
	}
}

void Game::UpdatePlayer()
{
	player->Update();
	player->UpdatePlayerWindowCollisions(window);

	// Take away player health if they collide with enemy
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			audio.enemyDeathSound.play();

			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			player->SetCurrentHealth(1);
		}
	}

	// Add health for colliding with health pack
	for (size_t i = 0; i < healthPacks.size(); i++)
	{
		if (player->GetGlobalBounds().intersects(healthPacks[i]->GetGlobalBounds()))
		{
			audio.healthPickupSound.play();

			delete healthPacks[i];
			healthPacks.erase(healthPacks.begin() + i);
			player->SetCurrentHealth(-1);
		}
	}

	// Game over if player health is 0
	if (player->SetCurrentHealth(0) <= 0)
	{
		audio.gameOverSound.play();

		gameOver = true;
	}
}

void Game::UpdateEnemies()
{
	speedTimer += 0.5f;
	spawnTimer += 0.5f;
	bool is_Enemy_Dead = false;
	int randomValue = rand() % 100 + 1;

	// Increase enemy speed and decrease time it takes for enemies to spawn as game goes on
	if (speedTimer >= timeWhenSpeedIncreases)
	{
		newSpeed += 0.1f;
		timeWhenEnemySpawns -= 1.f;
		speedTimer = 0.f;

		if (newSpeed >= 12.f)
		{
			newSpeed = 12.f;
			speedTimer = 0.f;
		}

		if (timeWhenEnemySpawns <= 8.f)
			timeWhenEnemySpawns = 8.f;
	}

	// Spawn enemy
	if (spawnTimer >= timeWhenEnemySpawns)
	{
		enemies.push_back(new Enemy(rand() % window->getSize().x - 25.f, -50.f, newSpeed));
		spawnTimer = 0.f;
	}

	// Update enemy
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->Update();
		sf::Vector2f dead_Enemy_Position = enemies[i]->GetPosition();

		// Move enemy inside window if spawned outside of it
		// Left
		if (enemies[i]->GetPosition().x <= 0.f)
			enemies[i]->SetPosition(0.f, enemies[i]->GetPosition().y);
		// Right
		if (enemies[i]->GetPosition().x + enemies[i]->GetGlobalBounds().width >= window->getSize().x)
			enemies[i]->SetPosition(window->getSize().x - enemies[i]->GetGlobalBounds().width, enemies[i]->GetPosition().y);

		// Remove enemy and bullet when they collide with each other
		for (size_t b = 0; b < bullets.size() && !is_Enemy_Dead; b++)
		{
			if (bullets[b]->GetGlobalBounds().intersects(enemies[i]->GetGlobalBounds()))
			{
				audio.enemyDeathSound.play();

				delete bullets[b];
				bullets.erase(bullets.begin() + b);

				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				player->SetPoints(10);

				is_Enemy_Dead = true;

				// Create random chance for health pack to spawn when enemy dies
				if (randomValue >= 95 && randomValue <= 100 && is_Enemy_Dead)
				{
					healthPacks.push_back(new HealthPack(textures["HEALTHPACK"], dead_Enemy_Position.x, dead_Enemy_Position.y));
				}
			}
		}

		// Remove enemy at bottom of screen
		if (!is_Enemy_Dead)
		{
			if (enemies[i]->GetGlobalBounds().top > window->getSize().y)
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				player->SetCurrentHealth(1);

				is_Enemy_Dead = true;
			}
		}
	}
}

void Game::UpdateHealthBar()
{
	// Resize health bar based on player health
	switch (player->SetCurrentHealth(0))
	{
	case 10:
		fullHealthBarSprite.setScale(1.f, 1.f);
		break;
	case 9:
		fullHealthBarSprite.setScale(0.9f, 1.f);
		break;
	case 8:
		fullHealthBarSprite.setScale(0.8f, 1.f);
		break;
	case 7:
		fullHealthBarSprite.setScale(0.7f, 1.f);
		break;
	case 6:
		fullHealthBarSprite.setScale(0.6f, 1.f);
		break;
	case 5:
		fullHealthBarSprite.setScale(0.5f, 1.f);
		break;
	case 4:
		fullHealthBarSprite.setScale(0.4f, 1.f);
		break;
	case 3:
		fullHealthBarSprite.setScale(0.3f, 1.f);
		break;
	case 2:
		fullHealthBarSprite.setScale(0.2f, 1.f);
		break;
	case 1:
		fullHealthBarSprite.setScale(0.1f, 1.f);
		break;
	case 0:
		fullHealthBarSprite.setScale(0.02f, 1.f);
		break;
	}
}

void Game::UpdateHealthPack()
{
	// Move health pack fully in screen if it's not
	for (size_t i = 0; i < healthPacks.size(); i++)
	{
		// Move from outside top of window to inside
		if (healthPacks[i]->GetPosition().y <= 0.f)
			healthPacks[i]->SetPosition(healthPacks[i]->GetPosition().x, 0.f);
	}
}

void Game::UpdateText()
{
	// Convert string stream to a single string for rendering GUI
	std::stringstream ss;

	ss << "Points: " << player->SetPoints(0) << std::endl;

	guiText.setString(ss.str());
}

void Game::UpdateGameOver()
{
	// If space is pressed on game over, reload all data and restart game
	if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		gameOver = false;

		// Delete memory
		delete window;
		
		// Restart game
		InitializeVariables();
		InitializeFonts();
		InitializeText();
		InitializeWindow();
		InitializeWorld();
		InitializeTextures();
		InitializePlayer();
		InitializeEnemies();
	}
}

void Game::Update()
{
	// Update entire application
	PollEvents();

	if (!gameOver && !gamePaused)
	{
		UpdatePause();
		UpdateInput();
		UpdatePlayer();
		UpdateBullets();
		UpdateEnemies();
		UpdateHealthBar();
		UpdateHealthPack();
		UpdateText();
	}

	if (gamePaused)
		UpdateGameWhenPaused();
	
	UpdateGameOver();
}

void Game::RenderWorld(sf::RenderTarget* target)
{
	// Draw background 
	target->draw(worldBackgroundSprite);
}

void Game::RenderHealthBar(sf::RenderTarget* target)
{
	// Draw health bar
	target->draw(fullHealthBarSprite);
}

void Game::RenderGUIText(sf::RenderTarget* target)
{
	// Draw GUI text
	target->draw(guiText);
}

void Game::Render()
{
	// Clear old frame
	window->clear();

	// Draw new frame
	// Render world background to window
	RenderWorld(window);

	// Render players health bar to window
	RenderHealthBar(window);

	// Render player to window
	player->Render(window);

	// Render bullets to window
	for (auto* bullet : bullets)
	{
		bullet->Render(window);
	}

	// Render enemies to window
	for (auto* enemy : enemies)
	{
		enemy->Render(window);
	}

	// Render health packs to window
	for (auto* health_Pack : healthPacks)
	{
		health_Pack->Render(window);
	}

	// Render GUI text to window
	RenderGUIText(window);

	// Draw pause menu text
	if (gamePaused)
	{
		window->draw(gamePausedText);
		window->draw(resumeOrQuitGameText);
	}

	// Draw game over & restart text
	if (gameOver)
	{
		window->draw(gameOverText);
		window->draw(restartGameText);
	}

	// Display new frame
	window->display();
}

// Game loop
void Game::Run()
{
	// Only while window is open
	while (IsRunning())
	{
		Update();
		Render();
	}
}
