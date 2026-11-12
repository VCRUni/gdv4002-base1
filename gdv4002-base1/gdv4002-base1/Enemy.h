#pragma once
#include "GameObject2D.h"
#include <glm/glm.hpp>

class Enemy : public GameObject2D
{
private:
	float phaseAngle; //radians
	float phaseVelocity; //angle changes per second

public:
	Enemy(glm::vec2 iniPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float initialPhase, float initialPhaseVelocity);

	void update(double tDelta) override;

};