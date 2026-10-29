#include "Engine.h"


// Function prototypes

void myUpdateScene(GLFWwindow* window, double tDelta);

// Global Variables


int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1000, 1000);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		fprintf(stderr, "Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//

	addObject("player", glm::vec2(1.0f, 1.00), (45.0f * 3.14159) / 180, glm::vec2(1.3f, 1.0f), "Resources\\Textures\\WiiParty.png", TextureProperties::NearestFilterTexture());
	addObject("ship", glm::vec2(-1.0f, -1.00), (45.0f * 3.14159) / 180, glm::vec2(0.5f, 0.5f), "Resources\\Textures\\player1_ship.png", TextureProperties::NearestFilterTexture());

	//
	// Set callback functions
	// 

	setUpdateFunction(myUpdateScene);

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

void myUpdateScene(GLFWwindow* window, double tDelta) {

	// add update code here 

	const float pi = 3.141593f;

	float playerthetaVelocity = glm::radians(30.f);

	float shipthetaVelocity = glm::radians(-90.f);

	GameObject2D* player1 = getObject("player");

	player1->orientation = player1->orientation + (playerthetaVelocity * tDelta);

	GameObject2D* ship = getObject("ship");

	ship->orientation = ship->orientation + (shipthetaVelocity * tDelta);

}
