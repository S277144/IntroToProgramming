#pragma once

#include <cmath>

struct Vector2
{
	float x{ 0.0f };
	float y{ 0.0f };

	Vector2() = default;
	Vector2(float x, float y) : x{ x }, y{ y } {}

	void add(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}

	void subtract(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void scale(float scalar)
	{
		x *= scalar;
		y *= scalar;
	}

	float magnitude()
	{
		return sqrtf(x * x + y * y);
	}

	void normalize()
	{
		float mag = magnitude();

		if (mag > 0.0f)
		{
			x /= mag;
			y /= mag;
		}
	}
};

