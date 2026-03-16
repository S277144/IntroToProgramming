#pragma once

#include "GameObject.h"
#include "Config.h"

enum class Size
{
	Large,
	Small
};

class Asteroid : public GameObject
{
public:
	Asteroid(Size sz);
	Asteroid(const Vector2& pos, Size sz);

	Size getSize() const { return _Size; }

private:
	void randomiseVelocity();

	const float MaxSpeed{ 1.5 };

	Size _Size;
};