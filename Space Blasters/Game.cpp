#include "Game.h"


// Private Functions
void Game::InitializeVariables()
{
	gameOver = false;
}

void Game::InitializeFonts()
{
	if (!font.loadFromFile("Fonts/Dosis-Light.ttf"))
		std::cout << "ERROR::GAME::FONT::DOSIS-LIGHT.TTF COULD NOT LOAD!" << std::endl;
}

void Game::InitializeText()
{
	// Set GUI text
	guiText.setFont(font);
	guiText.setFillColor(sf::Color::White);
	guiText.setPosition(15.f, 10.f);
	guiText.setCharacterSize(28);

	// Set Game Over text
	gameOverText.setFont(font);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setPosition(215.f, 230.f);
	gameOverText.setCharacterSize(80);
	gameOverText.setString("GAME OVER");

	// Set restart game text
	restartGameText.setFont(font);
	restartGameText.setFillColor(sf::Color::White);
	restartGameText.setPosition(270.f, 330.f);
	restartGameText.setCharacterSize(32);
	restartGameText.setString("Press Space to Restart");
}

void Game::InitializeWindow()
{
	videoMode = sf::VideoMode(800, 600);
	window = new sf::RenderWindow(videoMode, "Game 3", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);
}

void Game::InitializeWorld()
{
	if (!worldBackgroundTexture.loadFromFile("Textures/background1.jpg"))
		std::cout << "ERROR::GAME::BACKGROUND1.JPG COULD NOT LOAD!" << std::endl;

	worldBackground.setTexture(worldBackgroundTexture);
	worldBackground.setScale(0.45f, 0.6f);
}

void Game::InitializeTextures()
{
	textures["BULLET"] = new sf::Texture();
	textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::InitializePlayer()
{
	player = new Player();
}

void Game::InitializeEnemies()
{
	timeWhenEnemySpawns = 30.f;
	spawnTimer = timeWhenEnemySpawns;
}

// Constructor & Destructor
Game::Game()
{
	InitializeVariables();
	InitializeFonts();
	InitializeText();
	InitializeWindow();
	InitializeWorld();
	InitializeTextures();
	InitializePlayer();
	InitializeEnemies();
}

Game::~Game()
{
	delete window;
	delete player;

	// Delete textures
	for (auto& i : textures)
	{
		i.second;
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
}

// Accessors
const bool Game::IsRunning() const
{
	return window->isOpen();
}

const bool& Game::GetEndGame() const
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window->close();
	}
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
			10.f)
		);
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

	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			player->GetCurrentHealth(1);
		}
	}

	if (player->GetCurrentHealth(0) <= 0)
	{
		gameOver = true;
	}
}

void Game::UpdateEnemies()
{
	spawnTimer += 0.5f;
	bool is_Enemy_Dead = false;

	// Spawn enemy
	if (spawnTimer >= timeWhenEnemySpawns)
	{
		enemies.push_back(new Enemy(rand() % window->getSize().x - 25.f, -50.f));
		spawnTimer = 0.f;
	}

	// Update enemy
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->Update();

		// Remove enemy and bullet when they collide with each other
		for (size_t b = 0; b < bullets.size() && !is_Enemy_Dead; b++)
		{
			if (bullets[b]->GetGlobalBounds().intersects(enemies[i]->GetGlobalBounds()))
			{
				delete bullets[b];
				bullets.erase(bullets.begin() + b);

				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				player->GetPoints(10);

				is_Enemy_Dead = true;
			}
		}

		// Remove enemy at bottom of screen
		if (!is_Enemy_Dead)
		{
			if (enemies[i]->GetGlobalBounds().top > window->getSize().y)
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);

				is_Enemy_Dead = true;
			}
		}
	}
}

void Game::UpdateText()
{
	std::stringstream ss;

	ss << "Points: " << player->GetPoints(0) << std::endl
		<< "Health: " << player->GetCurrentHealth(0) << std::endl;

	guiText.setString(ss.str());
}

void Game::UpdateGameOver()
{
	if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		gameOver = false;
		delete window;
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
	PollEvents();

	if (!gameOver)
	{
		UpdateInput();
		UpdatePlayer();
		UpdateBullets();
		UpdateEnemies();
		UpdateText();
	}

	UpdateGameOver();
}

void Game::RenderWorld(sf::RenderTarget* target)
{
	target->draw(worldBackground);
}

void Game::RenderText(sf::RenderTarget* target)
{
	target->draw(guiText);
}

void Game::Render()
{
	// Clear old frame
	window->clear();

	// Draw new frame
	RenderWorld(window);

	player->Render(window);

	for (auto* bullet : bullets)
	{
		bullet->Render(window);
	}

	for (auto* enemy : enemies)
	{
		enemy->Render(window);
	}

	RenderText(window);

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
