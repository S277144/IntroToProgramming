#pragma once

#include "Animated_object.h"
#include "World.h"

class Enemy : public AnimatedObject
{
public:
	Enemy() = default;
	Enemy(float x, float y) : AnimatedObject(x, y) {}
	Enemy(const Vector2& position) : AnimatedObject(position) {}

private:
	void moveELeft();
	void moveERight();

};
