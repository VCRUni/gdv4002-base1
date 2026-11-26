#pragma once

// model snowflake particle

#include "GameObject2D.h"

class Snowflake : public GameObject2D
{
private:
	// linear movment
	float mass;
	glm::vec2 velocity;

	float angleChangePerSecond;

public:
	Snowflake(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond);

	void update(double tDelta) override;
};