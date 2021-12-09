#pragma once

#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#define WINDOW_WIDTH   1280
#define WINDOW_HEIGHT  720

#define PI                3.14159265359
#define TWO_PI            2 * PI
#define PI_DIV_TWO        PI / 2
#define THREE_PI_DIV_TWO  3 * PI / 2
#define ONE_DEG_IN_RAD    0.0174533


class Engine
{
private:
	// Player variables
	float playerPosX;
	float playerPosY;
	float playerDeltaRotX;
	float playerDeltaRotY;
	float playerAngle;

	// Map variables
	int m_MapPosX;
	int m_MapPosY;
	int mapOffsetX;
	int mapOffsetY;
	const int mapSizeX = 12;
	const int mapSizeY = 12;
	const int cellSize2D = 32;

	// Raycast variables
	const int numOfRays = 110;
	int ray;
	int r_MapPosX;
	int r_MapPosY;
	int vertRayMapPos;
	int horizRayMapPos;
	int mapPosition;
	int depthOfRay;
	float rayPosX;
	float rayPosY;
	float rayAngle;
	float horizRayDist;
	float horizRayPosX;
	float horizRayPosY;
	float vertRayDist;
	float vertRayPosX;
	float vertRayPosY;
	float finalRayDist;
	float correctAngLen;
	float wallStripHeight;
	float wallOffsetY;
	float xStep;
	float yStep;

	// Math
	float negInvTan;
	float negTan;

	// Private functions
	float Distance(float ax, float ay, float bx, float by);
	void DrawWorldMap();
	void DrawRays();
	void DrawPlayer();

public:
	// Constructor & Destructor
	Engine();
	~Engine();

	// Public functions
	void InitGame();
	void KeyInput(unsigned char& key, int& x, int& y);

	void Render();
};
