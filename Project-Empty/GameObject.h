#pragma once

#include "vector2.h"

class Gameobject
{
public:
	Gameobject(float x, float y, float ang, float radius) : _position{x ,y}, _angle{ang}, _radius{radius} {}

	float getX() const { return _position.x; }
	float getY() const { return _position.y; }
	float getAngle() const { return _angle; }

	float getradius() const { return _radius; }

protected:
	Vector2 _position;
	Vector2 _velocity{ 0.0f, 0.0f };
	float _angle;
	float _radius;
};

