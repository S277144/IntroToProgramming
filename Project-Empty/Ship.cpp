#include <numbers>
#include <iostream>

#include "Config.h"
#include "Ship.h"

void Ship::update()
{
	if (_isAccelerating)
	{
		_Velocity.x += std::cos(_Angle - Config::AngleOffset) * Config::ShipSpeed;
		_Velocity.y += std::sin(_Angle - Config::AngleOffset) * Config::ShipSpeed;
	}

	if (_Velocity.magnitude() > Config::ShipSpeed)
	{
		_Velocity.normalize();
		_Velocity.scale(Config::ShipSpeed);
	}

	_Velocity.scale(0.95f);

	GameObject::update();
}

void Ship::rotate(RotationDir dir)
{
	float modifier = dir == RotationDir::Left ? -1.0f : 1.0f;
	_Angle += RotationSpeed * modifier;

	if (_Angle < 0.0f)
		_Angle = 2.0f * std::numbers::pi_v<float>;
	else if (_Angle > 2.0f * std::numbers::pi_v<float>)
		_Angle = 0.0f;
}