#pragma once

#include <SDL3/SDL.h>

#include "GameObject.h"
#include "Config.h"

enum class RotationDir
{
	Left,
	Right
};

class Ship : public GameObject
{
public:
	Ship(float x, float y) : GameObject{ x, y, 0.0f, Config::ShipRadius }, _isAccelerating{ false } {}

	void update() override;
	void rotate(RotationDir dir);

	void startAccelerating() { _isAccelerating = true; }
	void stopAccelerating() { _isAccelerating = false; }

	void canFire() const { return _canFire; }
	void allowFire() { _canFire = true; }
	void fire() { _canFire = false; }

private:
	const float RotationSpeed{ 0.1f };

	bool _canFire{ true };
	bool _isAccelerating;
};