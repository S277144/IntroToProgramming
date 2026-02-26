#pragma once

#include <string>

namespace Config
{
	const std::string ProjectName = "Asteriods";

	constexpr int ScreenWidth = 1350;
	constexpr int ScreenHeight = 1350;

	constexpr float HalfScreenWidth = static_cast<float>(ScreenWidth) / 2;
	constexpr float HalfScreenHeight = static_cast<float>(ScreenHeight) / 2;
}
