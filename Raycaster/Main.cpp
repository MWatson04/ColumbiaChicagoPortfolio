#include "Engine.h"

Engine engine;

// Init window data using OpenGL
void InitOpenGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
}

// Render game using OpenGL
void RenderGameOpenGL()
{
	engine.Render();
}

// Reshape window back to original size
void Resize(int width, int height)
{
	glutReshapeWindow(1280, 720);
}

// Set up key input through OpenGL
void KeyInputOpenGL(unsigned char key, int x, int y)
{
	engine.KeyInput(key, x, y);
}

int main(int argc, char* argv[])
{
	// Init GLUT
	glutInit(&argc, argv);
	// Set up memory buffers
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set window size and position on screen (center of screen)
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) / 2) - (WINDOW_WIDTH / 2),
		(glutGet(GLUT_SCREEN_HEIGHT) / 2) - (WINDOW_HEIGHT / 2));
	// Create window
	glutCreateWindow("Raycaster");

	InitOpenGL();

	// Render game
	glutDisplayFunc(RenderGameOpenGL);
	// Used to always make sure window is original size
	glutReshapeFunc(Resize);
	glutKeyboardFunc(KeyInputOpenGL);

	// Init OpenGL drivers
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << err << "GLEW ERROR" << std::endl;
		return 1;
	}

	// End of application
	glutMainLoop();
	return 0;
}