#include "Engine.h"

#include "Textures/all_textures.ppm.bak"


// To be used to control key state for player actions
typedef struct KeyState
{
	int w, a, s, d, e;
};
KeyState Keys;  // Struct instance

// Init wallMap here for full file scope
int wallMap[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 2, 1,
	1, 0, 3, 0, 0, 3, 0, 0, 5, 0, 0, 1,
	1, 0, 3, 4, 3, 3, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 6, 0, 0, 3, 3, 3, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

// Used to return distance between player and rays end point
float Engine::Distance(float ax, float ay, float bx, float by)
{
	// Pythagorean theorem
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void Engine::InitGame()
{
	// Player variables
	playerPosX = 72.0f;
	playerPosY = 22.0f;
	playerAngle = -4.2;
	playerDeltaRotX = cos(playerAngle);
	playerDeltaRotY = sin(playerAngle);
	offsetFromWallX = 0;
	offsetFromWallY = 0;
	playerMapPosX = 0;
	playerMapPosY = 0;
	pPosX_add_OffsetX = 0;
	pPosX_sub_OffsetX = 0;
	pPosY_add_OffsetY = 0;
	pPosY_sub_OffsetY = 0;

	// Map variables
	m_MapPosX = 0;
	m_MapPosY = 0;
	mapOffsetX = 0;
	mapOffsetY = 0;

	// Raycast variables
	ray = 0;
	r_MapPosX = 0;
	r_MapPosY = 0;
	vertRayMapPos = 0;
	horizRayMapPos = 0;
	mapPosition = 0;
	depthOfRay = 0;  // Used to set how far ray can see
	rayPosX = 0.0f;
	rayPosY = 0.0f;
	rayAngle = 0.0f;
	horizRayDist = 0.0f;
	horizRayPosX = 0.0f;
	horizRayPosY = 0.0f;
	vertRayDist = 0.0f;
	vertRayPosX = 0.0f;
	vertRayPosY = 0.0f;
	finalRayDist = 0.0f;
	correctAngLen = 0.0f;
	wallStripHeight = 0.0f;
	wallOffsetY = 0.0f;
	stepX = 0.0f;
	stepY = 0.0f;

	// Textures
	shade = 0.0f;
	texturePosY = 0.0f;
	textureStepY = 0.0f;
	textureOffsetY = 0.0f;
	texturePosX = 0.0f;
	horizMapTexture = 0;
	vertMapTexture = 0;
	pixel = 0;
	redValue = 0;
	greenValue = 0;
	blueValue = 0;

	// Math
	negInvTan = 0.0f;
	negTan = 0.0f;
	frameOne = 0.0f;
	frameTwo = 0.0f;
	deltaTime = 0.0f;
}

float Engine::GetDeltaTime()
{
	frameTwo = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (frameTwo - frameOne);
	frameOne = frameTwo;

	return deltaTime;
}

// Draw 2D map to be used as mini map for player
void Engine::DrawMap()
{
	// Go through map positions and draw map
	for (m_MapPosY = 0; m_MapPosY < mapSizeY; m_MapPosY++)
	{
		for (m_MapPosX = 0; m_MapPosX < mapSizeX; m_MapPosX++)
		{
			if (wallMap[m_MapPosY * mapSizeX + m_MapPosX] == 1)
				glColor3f(1.0f, 0.0f, 0.0f);                           // Red for first texture in allTextures[]
			else if (wallMap[m_MapPosY * mapSizeX + m_MapPosX] == 2)
				glColor3f(0.0f, 1.0f, 0.0f);                           // Green for second texture in allTextures[]
			else if (wallMap[m_MapPosY * mapSizeX + m_MapPosX] == 3)
				glColor3f(0.0f, 0.0f, 1.0f);                           // Blue for third texture in allTextures[]
			else if (wallMap[m_MapPosY * mapSizeX + m_MapPosX] == 4)
				glColor3f(1.0f, 1.0f, 0.0f);                           // Yellow for fourth texture in allTextures[] (Doors)
			else if (wallMap[m_MapPosY * mapSizeX + m_MapPosX] == 5)
				glColor3f(0.0f, 1.0f, 1.0f);                           // Cyan for sixth texture in allTextures[]
			else if (wallMap[m_MapPosY * mapSizeX + m_MapPosX] == 6)
				glColor3f(1.0f, 0.0f, 1.0f);                           // Pink for sixth texture in allTextures[]
			else
				glColor3f(0.3f, 0.3f, 0.3f);                           // Grey for empty space


			// Use offsets to draw cells with an offset to each other that corresponds to the cells size
			mapOffsetX = m_MapPosX * cellSize2D;
			mapOffsetY = m_MapPosY * cellSize2D;

			// Draw map
			glBegin(GL_QUADS);
			glVertex2f(mapOffsetX, mapOffsetY);
			glVertex2f(mapOffsetX, mapOffsetY + cellSize2D);
			glVertex2f(mapOffsetX + cellSize2D, mapOffsetY + cellSize2D);
			glVertex2f(mapOffsetX + cellSize2D, mapOffsetY);
			glEnd();
		}
	}
}

void Engine::DrawFloor()
{
	// Set "floor" color before casting rays so it gets drawn over
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_QUADS);
	glVertex2i(0, WINDOW_HEIGHT / 2);
	glVertex2i(0, WINDOW_HEIGHT);
	glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
	glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	glEnd();
}

void Engine::DrawCeiling()
{
	// Set "sky" color before casting rays so it gets drawn over
	glColor3f(0.0f, 0.7f, 0.9f);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(0, WINDOW_HEIGHT / 2);
	glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	glVertex2i(WINDOW_WIDTH, 0);
	glEnd();
}

// Create, make checks for, and display rays to make "3D" world
void Engine::DrawWalls()
{
	// Push the start of the rays to the left by 30 degrees
	rayAngle = playerAngle - (ONE_DEG_IN_RAD * 30);
	if (rayAngle < 0)
		rayAngle += TWO_PI;
	if (rayAngle > TWO_PI)
		rayAngle -= TWO_PI;

	for (ray = 0; ray < numOfRays; ray++)
	{
		// ---Check horizontal line---
		depthOfRay = 0;
		horizRayDist = 1000000.0f;  // Default value is really high since looking for shortest distance
		horizRayPosX = playerPosX;
		horizRayPosY = playerPosY;
		negInvTan = -1 / tan(rayAngle);

		if (rayAngle > PI)  // Check if ray is looking up
		{
			// Round rays y position to nearest 16th value
			// Bit shift value corresponds with cellSize2D value
			rayPosY = (((int)playerPosY >> 4) << 4) - 0.0001;
			// Rays x value is the distance between the player and the rays y position
			rayPosX = (playerPosY - rayPosY) * negInvTan + playerPosX;

			// Go to next horizontal x and y position
			stepY = -cellSize2D;
			stepX = -stepY * negInvTan;
		}

		if (rayAngle < PI)  // Check if ray is looking down
		{
			// Round rays y position to nearest 16th value
			rayPosY = (((int)playerPosY >> 4) << 4) + cellSize2D;
			rayPosX = (playerPosY - rayPosY) * negInvTan + playerPosX;

			// Go to next horizontal x and y position
			stepY = cellSize2D;
			stepX = -stepY * negInvTan;
		}

		if (rayAngle == 0 || rayAngle == PI)  // Check if ray is looking straight left or right
		{
			// Set ray to look straight with a view distance of the whole map
			rayPosX = playerPosX;
			rayPosY = playerPosY;
			depthOfRay = 12;
		}

		while (depthOfRay < 12)
		{
			// Take rays hit position and divides by 16 to get value that can be stored as a position in the map array
			r_MapPosX = (int)(rayPosX) >> 4;
			r_MapPosY = (int)(rayPosY) >> 4;
			// Use x and y rays position to store a position in map array
			mapPosition = r_MapPosY * mapSizeX + r_MapPosX;

			// Check if mapPosition is in array and then check what its value is
			if (mapPosition > 0 && mapPosition < mapSizeX * mapSizeY && wallMap[mapPosition] > 0)
			{
				horizMapTexture = wallMap[mapPosition] - 1;

				// Store horizontal rays hit to use for coloring
				horizRayMapPos = wallMap[mapPosition];

				// Wall has been hit
				horizRayPosX = rayPosX;
				horizRayPosY = rayPosY;
				// Calculate distance of horizontal ray from player to end of ray
				horizRayDist = Distance(playerPosX, playerPosY, horizRayPosX, horizRayPosY);

				depthOfRay = 12;
			}
			else  // Wall hasn't been hit
			{
				// Move to next horizontal x and y position 
				rayPosX += stepX;
				rayPosY += stepY;
				depthOfRay += 1;
			}
		}

		// ---Check vertical line---
		/*
			This is the same as checking for a horizontal line except
			all of the x and y values in the first two if
			statements are flipped
		*/
		depthOfRay = 0;
		vertRayDist = 1000000.0f;
		vertRayPosX = playerPosX;
		vertRayPosY = playerPosY;
		negTan = -tan(rayAngle);

		if (rayAngle > PI_DIV_TWO && rayAngle < THREE_PI_DIV_TWO)  // Check if ray is looking left
		{
			rayPosX = (((int)playerPosX >> 4) << 4) - 0.0001;
			rayPosY = (playerPosX - rayPosX) * negTan + playerPosY;

			stepX = -cellSize2D;
			stepY = -stepX * negTan;
		}

		if (rayAngle < PI_DIV_TWO || rayAngle > THREE_PI_DIV_TWO)  // Check if ray is looking right
		{
			rayPosX = (((int)playerPosX >> 4) << 4) + cellSize2D;
			rayPosY = (playerPosX - rayPosX) * negTan + playerPosY;

			stepX = cellSize2D;
			stepY = -stepX * negTan;
		}

		if (rayAngle == 0 || rayAngle == PI)  // Check if ray is looking straight up or down
		{
			rayPosX = playerPosX;
			rayPosY = playerPosY;
			depthOfRay = 12;
		}

		while (depthOfRay < 12)
		{
			r_MapPosX = (int)(rayPosX) >> 4;
			r_MapPosY = (int)(rayPosY) >> 4;
			mapPosition = r_MapPosY * mapSizeX + r_MapPosX;

			if (mapPosition > 0 && mapPosition < mapSizeX * mapSizeY && wallMap[mapPosition] > 0)
			{
				vertMapTexture = wallMap[mapPosition] - 1;

				vertRayMapPos = wallMap[mapPosition];

				vertRayPosX = rayPosX;
				vertRayPosY = rayPosY;
				vertRayDist = Distance(playerPosX, playerPosY, vertRayPosX, vertRayPosY);

				depthOfRay = 12;
			}
			else
			{
				rayPosX += stepX;
				rayPosY += stepY;
				depthOfRay += 1;
			}
		}

		shade = 1.0f;  // Used to make darker and brighter walls with textures
		// Set ray position to the vertical ray if the vertical ray is the shortest
		if (vertRayDist < horizRayDist)
		{
			horizMapTexture = vertMapTexture;

			shade = 0.5f;

			rayPosX = vertRayPosX;
			rayPosY = vertRayPosY;

			finalRayDist = vertRayDist;
		}

		// Set ray position to the horizontal ray if the horizontal ray is the shortest
		if (horizRayDist < vertRayDist)
		{
			rayPosX = horizRayPosX;
			rayPosY = horizRayPosY;

			finalRayDist = horizRayDist;
		}

		// ---Draw "3D" walls---
		// Find distance between player angle and ray angle
		correctAngLen = playerAngle - rayAngle;
		if (correctAngLen < 0)
			correctAngLen += TWO_PI;
		if (correctAngLen > TWO_PI)
			correctAngLen -= TWO_PI;

		finalRayDist = finalRayDist * cos(correctAngLen);  // Fix fisheye (shorten the longest rays to be equal to the length of the center rays)

		// Make walls that are farther away smaller, and closer walls bigger
		wallStripHeight = (cellSize3D * WINDOW_HEIGHT) / finalRayDist;
		textureStepY = textureSize / wallStripHeight; 
		textureOffsetY = 0.0f;
		if (wallStripHeight > WINDOW_HEIGHT)
		{
			textureOffsetY = (wallStripHeight - WINDOW_HEIGHT) / 2;
			wallStripHeight = WINDOW_HEIGHT;
		}

		// Offset wall strips to center of screen on y axis
		wallOffsetY = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);


		// Texture walls
		texturePosY = textureOffsetY * textureStepY;
		texturePosX;
		if (shade == 1)
		{
			texturePosX = (int)(rayPosX / 2) % textureSize;
			if (rayAngle > PI)                                   // Depending on place of texture in the map, there are parts that might be flipped
				texturePosX = (textureSize - 1) - texturePosX;   // This if statement checks for this and fixes it
		}
		else
		{
			texturePosX = (int)(rayPosY / 2) % textureSize;
			if (rayAngle > PI_DIV_TWO && rayAngle < THREE_PI_DIV_TWO)
				texturePosX = (textureSize - 1) - texturePosX;
		}
		for (int i = 0; i < wallStripHeight; i++)
		{
			pixel = ((int)texturePosY * textureSize + (int)texturePosX) * 3 + (horizMapTexture * textureSize * textureSize * 3);
			redValue = allTextures[pixel - 1] * shade;
			greenValue = allTextures[pixel + 0] * shade;
			blueValue = allTextures[pixel + 1] * shade;

			// Draw points in loop for walls using OpenGL
			glPointSize(8.0f);                      // Draw points every 8th pixel
			glColor3ub(redValue, greenValue, blueValue);
			glBegin(GL_POINTS);
			glVertex2f(ray * 8, i + wallOffsetY);
			glEnd();

			texturePosY += textureStepY;
		}

		// Draws every new ray one degree to the right of the previous one
		// Without this, the rays would all draw on top of each other
		rayAngle += ONE_DEG_IN_RAD / 3;
		if (rayAngle < 0)
			rayAngle += TWO_PI;
		if (rayAngle > TWO_PI)
			rayAngle -= TWO_PI;
	}
}

// Set player color, size, and position on screen
void Engine::DrawPlayer()
{
	// Set player color and size on screen
	glColor3f(1.0f, 1.0f, 0.0f);
	glPointSize(7.5f);
	glBegin(GL_POINTS);
	glVertex2f(playerPosX, playerPosY);
	glEnd();

	// Draw line to see players rotation
	glLineWidth(2.5f);
	glBegin(GL_LINES);
	glVertex2f(playerPosX, playerPosY);
	glVertex2f(playerPosX + (playerDeltaRotX * rotLineLen), playerPosY + (playerDeltaRotY * rotLineLen));
	glEnd();
}

// Setup wall collisions for player moving forward
void Engine::PlayerCollisions()
{
	// Set up collision distance from player to wall
	if (playerDeltaRotX < 0)
		offsetFromWallX = -collisionDist;
	else
		offsetFromWallX = collisionDist;

	if (playerDeltaRotY < 0)
		offsetFromWallY = -collisionDist;
	else
		offsetFromWallY = collisionDist;

	// Set players position in map with x and y offsets
	playerMapPosX = playerPosX / cellSize2D;
	playerMapPosY = playerPosY / cellSize2D;
	// Set variables to be used to check the cell number in all directions from the player
	pPosX_add_OffsetX = (playerPosX + offsetFromWallX) / cellSize2D;  // Divide by cell size to get position for map array
	pPosX_sub_OffsetX = (playerPosX - offsetFromWallX) / cellSize2D;
	pPosY_add_OffsetY = (playerPosY + offsetFromWallY) / cellSize2D;
	pPosY_sub_OffsetY = (playerPosY - offsetFromWallY) / cellSize2D;
}

// Setup wall collisions for player moving backward
bool Engine::PlayerMoveBackward()
{
	// Check if player is moving backward to an empty space in the map
	if (wallMap[playerMapPosY * mapSizeX + pPosX_sub_OffsetX] == 0)
	{
		return true;
	}
	if (wallMap[pPosY_sub_OffsetY * mapSizeX + playerMapPosX] == 0)
	{
		return true;
	}

	return false;
}

// Make check for player to open door
bool Engine::OpenDoors()
{
	// Player can open the door if the map position in front of it is equal to 4
	if (wallMap[pPosY_add_OffsetY * mapSizeX + pPosX_add_OffsetX] == 4)
	{
		return true;
	}

	return false;
}

// Set key state to true if player presses a key
void Engine::KeyPressed(unsigned char& key, int& x, int& y)
{
	if (key == 'a')
		Keys.a = true;

	if (key == 'd')
		Keys.d = true;

	if (key == 'w')
		Keys.w = true;

	if (key == 's')
		Keys.s = true;

	if (key == 'e')
		Keys.e = true;

	glutPostRedisplay();
}

// Set key state to false if player releases a pressed key
void Engine::KeyReleased(unsigned char& key, int& x, int& y)
{
	if (key == 'a')
		Keys.a = false;

	if (key == 'd')
		Keys.d = false;

	if (key == 'w')
		Keys.w = false;

	if (key == 's')
		Keys.s = false;

	if (key == 'e')
		Keys.e = false;

	glutPostRedisplay();
}

// Player controller
oid Engine::KeyInput()
{
	PlayerCollisions();
	float delta_Time = GetDeltaTime();

	// Rotate left or right and move forward or backward if in an empty space
	if (Keys.a)
	{
		playerAngle -= lookSensitivity * delta_Time;

		if (playerAngle < 0)
			playerAngle += TWO_PI;

		playerDeltaRotX = cos(playerAngle);  // Calculate cos and sin to get x and y change in player rotation
		playerDeltaRotY = sin(playerAngle);
	}

	if (Keys.d)
	{
		playerAngle += lookSensitivity * delta_Time;

		if (playerAngle > TWO_PI)
			playerAngle -= TWO_PI;

		playerDeltaRotX = cos(playerAngle);
		playerDeltaRotY = sin(playerAngle);
	}

	if (Keys.w)
	{
		// Check if player is moving forward to an empty space in the map
		if (wallMap[playerMapPosY * mapSizeX + pPosX_add_OffsetX] == 0)
		{
			playerPosX += playerDeltaRotX * moveSpeed * delta_Time;         // Move player in direction based on players rotation angle
		}
		if (wallMap[pPosY_add_OffsetY * mapSizeX + playerMapPosX] == 0)
		{
			playerPosY += playerDeltaRotY * moveSpeed * delta_Time;
		}
	}

	if (Keys.s)
	{
		// Check if player is moving backward to an empty space in the map
		if (wallMap[playerMapPosY * mapSizeX + pPosX_sub_OffsetX] == 0)
		{
			playerPosX -= playerDeltaRotX * moveSpeed * delta_Time;
		}
		if (wallMap[pPosY_sub_OffsetY * mapSizeX + playerMapPosX] == 0)
		{
			playerPosY -= playerDeltaRotY * moveSpeed * delta_Time;
		}
	}

	// Open doors by setting space with door to 0 so it becomes empty
	if (Keys.e)
	{
		// Player can open the door if the map position in front of it is equal to 4
		if (wallMap[pPosY_add_OffsetY * mapSizeX + pPosX_add_OffsetX] == 4)
		{
			wallMap[pPosY_add_OffsetY * mapSizeX + pPosX_add_OffsetX] = 0;
		}
	}

	glutPostRedisplay();
}

// Constructor & Destructor
Engine::Engine()
{
	InitGame();
}

Engine::~Engine()
{

}

void Engine::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	KeyInput();
	DrawFloor();
	DrawCeiling();
	DrawWalls();
	DrawMap();
	DrawPlayer();

	glutSwapBuffers();
}
