#pragma once

#include <SDL3\SDL.h>

#include "gameobject.h"

class Player : public Gameobject
{
public:
	Player(float x, float y) : Gameobject{ x, y, 0.0f, 1.0f }, rect{ x, y, 100.0f, 100.0f }
    {
		
    }

    SDL_FRect rect;
};