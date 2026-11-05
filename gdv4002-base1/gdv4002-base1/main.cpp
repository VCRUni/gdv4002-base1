#include "Engine.h"
#include "keys.h"
#include <bitset>
#include <math.h>


// Function prototypes

void myUpdateScene(GLFWwindow* window, double tDelta);
void mykeyboardhandler(GLFWwindow*, int, int, int, int);

// Global Variables

std::bitset<5>keys{ 0x0 };


int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		fprintf(stderr, "Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//

	addObject("player", glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), "Resources\\Textures\\player1_ship.png", TextureProperties::NearestFilterTexture());

	addObject("enemy", glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), "Resources\\Textures\\alien01.png", TextureProperties::NearestFilterTexture());
	addObject("enemy", glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), "Resources\\Textures\\alien01.png", TextureProperties::NearestFilterTexture());
	addObject("enemy", glm::vec2(2.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), "Resources\\Textures\\alien01.png", TextureProperties::NearestFilterTexture());

	//
	// Set callback functions
	// 

	setUpdateFunction(myUpdateScene);
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

float enemyPhase[3] = { 2.0f, 4.0f, 0.0f };

float enemyPhaseVelocity[3] = { 
 glm::radians(85.0f),
 glm::radians(90.0f),
 glm::radians(95.0f) };

void myUpdateScene(GLFWwindow* window, double tDelta) {

	// add update code here 
	GameObjectCollection enemies = getObjectCollection("enemy");
	for (int i = 0; i < enemies.objectCount; i++)
	{
		enemies.objectArray[i]->position.y = sinf(enemyPhase[i]); // assume phase stored in radians so no conversion needed 
		enemyPhase[i] += enemyPhaseVelocity[i] * tDelta;
	}
	
	static float playerspeed = 1.0f;
	static float playertorgue = glm::radians(70.0f);

	GameObject2D* player = getObject("player");

	if (keys.test(key::W) == true)
	{
		player->position.x += (cos(player->orientation) * playerspeed) * (float)tDelta;
		player->position.y += (sin(player->orientation) * playerspeed) * (float)tDelta;
	}
	if (keys.test(key::S) == true)
	{
		player->position.x -= (cos(player->orientation) * playerspeed) * (float)tDelta;
		player->position.y -= (sin(player->orientation) * playerspeed) * (float)tDelta;
	}
	if (keys.test(key::A) == true)
	{
		player->orientation += playertorgue * (float)tDelta;
	}
	if (keys.test(key::D) == true)
	{
		player->orientation -= playertorgue * (float)tDelta;
	}
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
