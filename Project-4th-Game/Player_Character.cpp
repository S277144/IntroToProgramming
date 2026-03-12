#include "Player_Character.h"

void PlayerCharacter::onPressed(Control control)
{
	switch (control)
	{
	case Control::Left:
		moveLeft();
		setAnimation("walk");
		break;
	case Control::Right:
		moveRight();
		setAnimation("walk");
		break;
	}
}

void PlayerCharacter::onReleased(Control control)
{
	switch (control)
	{
	case Control::Left:
	case Control::Right:
		_velocity.x = 0.0f;
		setAnimation("idle");
		break;
	case Control::Jump:
		setAnimation("jump");
		Jump();
	}
}

void PlayerCharacter::moveLeft()
{
	_direction = Direction::Left;
	_velocity.x = -50;
}

void PlayerCharacter::moveRight()
{
	_direction = Direction::Right;
	_velocity.x = 50;
}

void PlayerCharacter::Jump()
{
	if (_velocity.y >= 0.0f)
		_velocity.x = -100;
}