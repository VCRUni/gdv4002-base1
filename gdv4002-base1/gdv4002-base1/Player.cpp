#include "keys.h"
#include <bitset>
#include <math.h>
#include "Player.h"
#include "Engine.h"

extern std::bitset<5>keys;
extern glm::vec2 gravity;

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) 
{
	this->mass = mass;

	velocity = glm::vec2(0.0f, 0.0f); // default velocity to 0
}

void Player::update(double tDelta) 
{
	// set variables
	glm::vec2 F = glm::vec2(0.0f, 0.0f);
	float R = 0.0f;

	const float thrust = 2.0f;
	
	
	// set forces
	if (keys.test(key::W) == true)
	{
		F += glm::vec2(cos(orientation) * thrust, sin(orientation) * thrust);
	}
	if (keys.test(key::S) == true)
	{
		F -= glm::vec2(cos(orientation) * thrust, sin(orientation) * thrust);
	}
	if (keys.test(key::A) == true)
	{
		R += glm::radians(100.f);
	}
	if (keys.test(key::D) == true)
	{
		R -= glm::radians(100.f);
	}

	// applying gravity
	F += gravity;

	// add impulsive force
	if (position.y < -getViewplaneHeight() / 2.0f)
	{
		F += glm::vec2(0.0f, 5.f);
	}
	if (position.y > getViewplaneHeight() / 2.0f)
	{
		F += glm::vec2(0.0f, -5.f);
	}
	if (position.x < -getViewplaneWidth() / 2.0f)
	{
		F += glm::vec2(5.f, 0.0f);
	}
	if (position.x > getViewplaneWidth() / 2.0f)
	{
		F += glm::vec2(-5.f, 0.0f);
	}

	// calculate acceleration
	glm::vec2 a = F * (1.0f / mass);

	// integrate to get new velocity
	velocity = velocity + (a * (float)tDelta);

	// integrate tp get new position
	position = position + (velocity * (float)tDelta);
	orientation = orientation + (R * (float)tDelta);
}