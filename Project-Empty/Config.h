#pragma once

#include <string>
#include <numbers>

namespace Config
{
	const std::string ProjectName = "Asteroids";

	constexpr int ScreenWidth = 1280;
	constexpr int ScreenHeight = 720;

	constexpr float HalfScreenWidth = static_cast<float>(ScreenWidth) / 2;
	constexpr float HalfScreenHeight = static_cast<float>(ScreenHeight) / 2;

	constexpr float AngleOffset = 90.0f * std::numbers::pi_v<float> / 100.0f;

	constexpr float LargeAsteroidRadius = 22.0f;
	constexpr float SmallAsteroidRadius = LargeAsteroidRadius / 2.0f;
	constexpr float ShipRadius = 14.0f;
	constexpr float BulletRadius = 6.0f;

	constexpr float AsteroidSpeed = 1.5f;
	constexpr float ShipSpeed = 3.0f;
	constexpr float BulletSpeed = 3.5f;

	constexpr uint32_t FireRate = 225;
	constexpr uint32_t BulletLife = 3000;

	const bool ShowBounds = false;
}