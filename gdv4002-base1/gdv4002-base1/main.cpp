#include "Engine.h"
#include "keys.h"
#include "player.h"
#include "Enemy.h"
#include <bitset>
#include <math.h>


// Function prototypes

void myUpdateScene(GLFWwindow* window, double tDelta);
void mykeyboardhandler(GLFWwindow*, int, int, int, int);

// Global Variables

std::bitset<5>keys{ 0x0 };
glm::vec2 gravity = glm::vec2(0.0f, -0.5f);


int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 5.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		fprintf(stderr, "Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//

	GLuint playerTexture = loadTexture("Resources\\Textures\\player1_ship.png");
	Player* mainPlayer = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 1.0f);
    addObject("player", mainPlayer);

	// 1. Load enemy texture  
	GLuint enemyTexture = loadTexture("Resources\\Textures\\alien01.png");

	// 2. Create enemy objects 
	Enemy* enemy1 = new Enemy(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(45.0f));
	Enemy* enemy2 = new Enemy(glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(90.0f));
	Enemy* enemy3 = new Enemy(glm::vec2(2.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), enemyTexture, 0.0f, glm::radians(60.0f));

	// Add enemy objects to the engine 
	addObject("enemy1", enemy1);
	addObject("enemy2", enemy2);
	addObject("enemy3", enemy3);

	//
	// Set callback functions
	// 
	setKeyboardHandler(mykeyboardhandler);
	listGameObjectKeys();
	listObjectCounts();

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

void mykeyboardhandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// if key was pressed
	if (action == GLFW_PRESS)
	{
		// which key?
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// quit the window
			glfwSetWindowShouldClose(window, true);
			break;
		case GLFW_KEY_W:
		    keys[key::W] = true;
			break;
		case GLFW_KEY_S:
			keys[key::S] = true;
			break;
		case GLFW_KEY_A:
			keys[key::A] = true;
			break;
		case GLFW_KEY_D:
			keys[key::D] = true;
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		// key release events
		switch (key)
		{
		case GLFW_KEY_W:
			keys[key::W] = false;
			break;
		case GLFW_KEY_S:
			keys[key::S] = false;
			break;
		case GLFW_KEY_A:
			keys[key::A] = false;
			break;
		case GLFW_KEY_D:
			keys[key::D] = false;
			break;
		}
	}
}
