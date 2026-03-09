#pragma once

#include "Player_Character.h";
#include "Animated_Object.h";
#include "Resource_Manager.h";
#include "World.h";
#include <cstdint>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_scancode.h>

enum class Control 
{
	Left,
	Right,
	Jump
};

struct Clock
{
	uint64_t last_tick_time{ 0 };
	uint64_t delta = 0;

	void tick()
	{
		uint64_t tick_time = SDL_GetTicks();
		delta = tick_time - last_tick_time;
		last_tick_time = tick_time;
	}
};

struct KeyBind
{
	SDL_Scancode key{ SDL_SCANCODE_0 };
	bool isPressed{ false };
	Control control{ Control::Left };

};