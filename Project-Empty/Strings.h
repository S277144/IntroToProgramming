#pragma once

#include <array>
#include <string>

namespace UI
{
	enum class textSize
	{
		Game,
		Menu
	};

	struct Text
	{
		std::string str;
		textSize size;
	};

	const std::array<Text, 8> strings
	{
		Text{"asteroids", textSize::Menu},
		Text{"new game", textSize::Menu},
		Text{"quit", textSize::Menu},
		Text{"game over", textSize::Menu},
		Text{"fire to restart", textSize::Menu},
		Text{"escape to quit", textSize::Menu},
		Text{"score", textSize::Game},
		Text{"lives", textSize::Game},
	};
}