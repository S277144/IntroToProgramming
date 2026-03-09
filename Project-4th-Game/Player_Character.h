#pragma once

#include "Animated_object.h"

enum class Control
{
	Left,
	Right,
	Jump
};

class PlayerCharacter : public AnimatedObject
{
public:
	PlayerCharacter() = default;
	PlayerCharacter(float x, float y) : AnimatedObject (x, y) {}
	PlayerCharacter(const Vector2& position) : AnimatedObject(position) {}

	void onPressed(Control control);
	void onReleased(Control control);

private:
	void moveLeft();
	void moveRight();
	void Jump();
};