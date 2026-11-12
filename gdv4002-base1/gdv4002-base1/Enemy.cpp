#include "Enemy.h"

Enemy::Enemy(glm::vec2 iniPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float initialPhase, float initialPhaseVelocity) : GameObject2D(iniPosition, initOrientation, initSize, initTextureID)
{
	phaseAngle = initialPhase;
	phaseVelocity = initialPhaseVelocity;
}

void Enemy::update(double tDelta)
{
	// set position based on phaseAngle
	position.y = sinf(phaseAngle);

	//update phase angle based on velocity
	phaseAngle += phaseVelocity * tDelta;

}