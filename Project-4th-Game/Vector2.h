#pragma once

#include <cmath>

struct Vector2
{
	Vector2() : x{ 0.0f }, y{ 0.0f } {}
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(const Vector2& other) { x = other.x; y = other.y; }

	float x;
	float y;

	Vector2& operator=(const Vector2& rhs) = default;

	Vector2 operator+(const Vector2& rhs) const 
	{
		return { x + rhs.x, y + rhs.y };
	}

	Vector2& operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2 operator-(const Vector2& rhs) const
	{
		return { x - rhs.x, y - rhs.y };
	}

	Vector2& operator-=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2 operator*(const float rhs) const
	{
		return { x * rhs, y * rhs };
	}

	Vector2& operator*=(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vector2 operator/(const float rhs) const
	{
		return { x / rhs, y / rhs };
	}

	Vector2& operator/=(const float rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	bool operator==(const Vector2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator!=(const Vector2& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}

	float dot(const Vector2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	float magnitude() const
	{
		return sqrtf(x * x + y * y);
	}

	void normalise()
	{
		float mag = magnitude();

		if (mag <= 0.0f) return;

		x /= mag;
		y /= mag;
	}
};