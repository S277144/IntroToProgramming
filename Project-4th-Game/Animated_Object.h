#pragma once

#include <string>
#include <unordered_map>
#include <Vector>

#include "Config.h"
#include "Game_Object.h"

enum class Direction
{
	Left,
	Right
};

struct Animation
{
	SDL_Texture* texture{ nullptr };
	std::vector<SDL_FRect> frames{};

};
