#include "Missile.h"


void Missile::move()
{
	float dx = getPosition().x - target->getPosition().x;
	float dy = getPosition().y - target->getPosition().y;
	vel.x = dx * mag / hypotf(dx, dy);
	vel.y = dy * mag / hypotf(dx, dy);
}