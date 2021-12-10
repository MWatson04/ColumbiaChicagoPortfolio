#include "Engine.h"

int door;
// Init worldMap here for full file scope
int worldMap[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 1,
	1, 0, 3, 0, 0, 3, 0, 0, 2, 0, 0, 1,
	1, 0, 3, 4, 3, 3, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 2, 0, 0, 3, 3, 3, 1,
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
	playerPosX = 50.0f;
	playerPosY = 75.0f;
	playerAngle = 0;
	playerDeltaRotX = cos(playerAngle) * moveSpeed;
	playerDeltaRotY = sin(playerAngle) * moveSpeed;
	offsetFromWallX = 0;
	offsetFromWallY = 0;
	playerMapPosX = 0;
	playerMapPosY = 0;
	a_PlayerCollOffsetX = 0;
	s_PlayerCollOffsetX = 0;
	a_PlayerCollOffsetY = 0;
	s_PlayerCollOffsetY = 0;

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
	xStep = 0.0f;
	yStep = 0.0f;

	// Math
	negInvTan = 0.0f;
	negTan = 0.0f;
}

// Private functions
void Engine::DrawWorldMap()
{
	// Go through map positions and draw map
	for (m_MapPosY = 0; m_MapPosY < mapSizeY; m_MapPosY++)
	{
		for (m_MapPosX = 0; m_MapPosX < mapSizeX; m_MapPosX++)
		{
			if (worldMap[m_MapPosY * mapSizeX + m_MapPosX] == 1)
				glColor3f(1.0f, 0.0f, 0.0f);                           // Red for walls
			else if (worldMap[m_MapPosY * mapSizeX + m_MapPosX] == 2)
				glColor3f(0.0f, 1.0f, 0.0f);                           // Green for pillars
			else if (worldMap[m_MapPosY * mapSizeX + m_MapPosX] == 3)
				glColor3f(0.0f, 0.0f, 1.0f);                           // Blue for rooms
			else if (worldMap[m_MapPosY * mapSizeX + m_MapPosX] == 4)
				glColor3f(1.0f, 1.0f, 0.0f);                           // Yellow for doors
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

void Engine::DrawWalls()
{
	// Set "sky" color before casting rays so it gets drawn over
	glColor3f(0.0f, 0.7f, 0.9f); 
	glBegin(GL_QUADS); 
	glVertex2i(0, 0);
	glVertex2i(0, WINDOW_HEIGHT / 2);
	glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	glVertex2i(WINDOW_WIDTH, 0);
	glEnd();

	// Set "floor" color before casting rays so it gets drawn over
	glColor3f(0.2f, 0.2f, 0.2f); 
	glBegin(GL_QUADS); 
	glVertex2i(0, WINDOW_HEIGHT / 2);
	glVertex2i(0, WINDOW_HEIGHT);
	glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
	glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	glEnd();

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
			// Round rays y position to nearest 32nd value
			// Bit shift value corresponds with cellSize2D value
			rayPosY = (((int)playerPosY >> 4) << 4) - 0.0001;
			// Rays x value is the distance between the player and the rays y position
			rayPosX = (playerPosY - rayPosY) * negInvTan + playerPosX;

			// Go to next horizontal x and y position
			yStep = -cellSize2D;
			xStep = -yStep * negInvTan;
		}

		if (rayAngle < PI)  // Check if ray is looking down
		{
			// Round rays y position to nearest 32nd value
			rayPosY = (((int)playerPosY >> 4) << 4) + cellSize2D;
			rayPosX = (playerPosY - rayPosY) * negInvTan + playerPosX;

			// Go to next horizontal x and y position
			yStep = cellSize2D;
			xStep = -yStep * negInvTan;
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
			// Take rays hit position and divide it by 32 to get position in worldMap array
			r_MapPosX = (int)(rayPosX) >> 4;
			r_MapPosY = (int)(rayPosY) >> 4;
			mapPosition = r_MapPosY * mapSizeX + r_MapPosX;

			// Check if mapPosition is in array and then check what its value is
			if (mapPosition > 0 && mapPosition < mapSizeX * mapSizeY && worldMap[mapPosition] != 0)
			{
				// Store horizontal rays hit to use for coloring
				horizRayMapPos = worldMap[mapPosition];

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
				rayPosX += xStep;
				rayPosY += yStep;
				depthOfRay += 1;
			}
		}

		// ---Check vertical line---
		/*
			This is the same as checking for a horizontal line except
			the all x and y values in the first two if 
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

			xStep = -cellSize2D;
			yStep = -xStep * negTan;
		}

		if (rayAngle < PI_DIV_TWO || rayAngle > THREE_PI_DIV_TWO)  // Check if ray is looking right
		{
			rayPosX = (((int)playerPosX >> 4) << 4) + cellSize2D;
			rayPosY = (playerPosX - rayPosX) * negTan + playerPosY;

			xStep = cellSize2D;
			yStep = -xStep * negTan;
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

			if (mapPosition > 0 && mapPosition < mapSizeX * mapSizeY && worldMap[mapPosition] != 0)
			{
				vertRayMapPos = worldMap[mapPosition];

				vertRayPosX = rayPosX;
				vertRayPosY = rayPosY;
				vertRayDist = Distance(playerPosX, playerPosY, vertRayPosX, vertRayPosY);

				depthOfRay = 12;
			}
			else
			{
				rayPosX += xStep;
				rayPosY += yStep;
				depthOfRay += 1;
			}
		}

		// Set ray position to the vertical ray if the vertical ray is the shortest
		if (vertRayDist < horizRayDist)
		{
			rayPosX = vertRayPosX;
			rayPosY = vertRayPosY;

			finalRayDist = vertRayDist;

			// Set "brighter" colors for vertical walls
			if (vertRayMapPos == 1)
				glColor3f(0.9f, 0.0f, 0.0f);
			else if (vertRayMapPos == 2)
				glColor3f(0.0f, 0.9f, 0.0f);
			else if (vertRayMapPos == 3)
				glColor3f(0.0f, 0.0f, 0.9f);
			else if (vertRayMapPos == 4)
				glColor3f(0.9f, 0.9f, 0.0f);
		}

		// Set ray position to the horizontal ray if the horizontal ray is the shortest
		if (horizRayDist < vertRayDist)
		{
			rayPosX = horizRayPosX;
			rayPosY = horizRayPosY;

			finalRayDist = horizRayDist;

			// Set "shaded" colors for horizontal walls
			if (horizRayMapPos == 1)
				glColor3f(0.6f, 0.0f, 0.0f);
			else if (horizRayMapPos == 2)
				glColor3f(0.0f, 0.6f, 0.0f);
			else if (horizRayMapPos == 3)
				glColor3f(0.0f, 0.0f, 0.6f);
			else if (horizRayMapPos == 4)
				glColor3f(0.6f, 0.6f, 0.0f);
		}

		// Draw ray from player to where the ray has made a hit
		glLineWidth(2.0f);
		glBegin(GL_LINES);
		glVertex2f(playerPosX, playerPosY);  // From player position
		glVertex2f(rayPosX, rayPosY);        // To end of ray position
		glEnd();

		// ---Draw "3D" walls---
		// Find distance between player angle and ray angle
		correctAngLen = playerAngle - rayAngle;
		if (correctAngLen < 0)
			correctAngLen += TWO_PI;
		if (correctAngLen > TWO_PI)
			correctAngLen -= TWO_PI;

		finalRayDist = finalRayDist * cos(correctAngLen);  // Fix fisheye (shorten the longest rays to be equal to the length of the center rays)

		// Make walls that are farther away smaller, and closer walls bigger
		wallStripHeight = (cellSize2D * WINDOW_HEIGHT) / finalRayDist;
		if (wallStripHeight > WINDOW_HEIGHT)
			wallStripHeight = WINDOW_HEIGHT;

		// Offset wall strips to center of screen on y axis
		wallOffsetY = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);

		// Draw lines for walls using OpenGL
		glLineWidth(8.0f);                                        // Draw lines every 8th pixel
		glBegin(GL_LINES);
		glVertex2f(ray * 8, wallOffsetY);  // Start drawing walls on right half of screen
		glVertex2f(ray * 8, 
			wallStripHeight + wallOffsetY);                       // Draw walls from 0 (top of screen) to line_Height (bottom of screen at max line_Height)
		glEnd();

		// Draws every new ray one degree to the right of the previous one
		// Without this, the rays would all draw on top of each other
		rayAngle += ONE_DEG_IN_RAD / 2.6;
		if (rayAngle < 0)
			rayAngle += TWO_PI;
		if (rayAngle > TWO_PI)
			rayAngle -= TWO_PI;
	}
}

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

bool Engine::PlayerMoveForward()
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
	// Set add and subtract variables to be used to check if theres a wall in front and behind the player
	a_PlayerCollOffsetX = (playerPosX + offsetFromWallX) / cellSize2D;
	s_PlayerCollOffsetX = (playerPosX - offsetFromWallX) / cellSize2D;
	a_PlayerCollOffsetY = (playerPosY + offsetFromWallY) / cellSize2D;
	s_PlayerCollOffsetY = (playerPosY - offsetFromWallY) / cellSize2D;

	// Check if player is moving forward to an empty space in the map
	if (worldMap[playerMapPosY * mapSizeX + a_PlayerCollOffsetX] == 0 
		&& worldMap[a_PlayerCollOffsetY * mapSizeX + playerMapPosX] == 0)
	{
		return true;
	}

	return false;
}

bool Engine::PlayerMoveBackward()
{
	// Check if player is moving backward to an empty space in the map
	if (worldMap[playerMapPosY * mapSizeX + s_PlayerCollOffsetX] == 0
		&& worldMap[s_PlayerCollOffsetY * mapSizeX + playerMapPosX] == 0)
	{
		return true;
	}

	return false;
}

bool Engine::OpenDoors()
{
	// Player can open the door if the map position in front of it is equal to 4
	if (worldMap[a_PlayerCollOffsetY * mapSizeX + a_PlayerCollOffsetX] == 4)
	{
		return true;
	}

	return false;
}

void Engine::KeyInput(unsigned char& key, int& x, int& y)
{
	bool can_Move_Forward = PlayerMoveForward();
	bool can_Move_Backward = PlayerMoveBackward();
	bool can_Open_Door = OpenDoors();

	// Rotate left or right and move forward or backward if in an empty space
	if (key == 'a')
	{
		playerAngle -= 0.1f;

		if (playerAngle < 0)
			playerAngle += TWO_PI;

		playerDeltaRotX = cos(playerAngle) * moveSpeed;  // Calculate cos and sin to get x and y change in player rotation
		playerDeltaRotY = sin(playerAngle) * moveSpeed;
	}

	if (key == 'd')
	{
		playerAngle += 0.1f;

		if (playerAngle > TWO_PI)
			playerAngle -= TWO_PI;

		playerDeltaRotX = cos(playerAngle) * moveSpeed;
		playerDeltaRotY = sin(playerAngle) * moveSpeed;
	}
	
	if (key == 'w' && can_Move_Forward)
	{
		playerPosX += playerDeltaRotX;  // Move player in direction based on players rotation angle
		playerPosY += playerDeltaRotY;
	}

	if (key == 's' && can_Move_Backward)
	{
		playerPosX -= playerDeltaRotX;
		playerPosY -= playerDeltaRotY;
	}

	// Open doors by setting space with door to 0 so it becomes empty
	if (key == 'e' && can_Open_Door)
	{
		worldMap[a_PlayerCollOffsetY * mapSizeX + a_PlayerCollOffsetX] = 0;
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

// Public functions
void Engine::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawWalls();
	DrawWorldMap();
	DrawPlayer();

	glutSwapBuffers();
}
