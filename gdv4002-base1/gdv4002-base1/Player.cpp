#include "keys.h"
#include <bitset>
#include <math.h>
#include "Player.h"

extern std::bitset<5>keys;

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float initialPlayerSpeed, float initalPlayerTorque) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) 
{
	playerSpeed = initialPlayerSpeed;
	PlayerTorque = glm::radians(initalPlayerTorque);
}

void Player::update(double tDelta) 
{
	// Unlike our myUpdate function, we're already 'in' the player object, so no need to call getObject as we did before :) 
	if (keys.test(key::W) == true)
	{
		position.x += (cos(orientation) * playerSpeed) * (float)tDelta;
		position.y += (sin(orientation) * playerSpeed) * (float)tDelta;
	}
	if (keys.test(key::S) == true)
	{
		position.x -= (cos(orientation) * playerSpeed) * (float)tDelta;
		position.y -= (sin(orientation) * playerSpeed) * (float)tDelta;
	}
	if (keys.test(key::A) == true)
	{
		orientation += PlayerTorque * (float)tDelta;
	}
	if (keys.test(key::D) == true)
	{
		orientation -= PlayerTorque * (float)tDelta;
	}
}