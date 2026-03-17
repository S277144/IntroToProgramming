#pragma once

#include <functional>
#include <memory>

#include "Enemy.h"
#include "Player_Character.h"
#include "Animated_Object.h"
#include "Resource_Manager.h"
#include "World.h"
#include <cstdint>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_scancode.h>

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
	std::function<void(Control control)> onPress;
	std::function<void(Control control)> onRelease;
};

class Game
{
public:
	Game()
	{
		Initialize();
	}

	~Game()
	{
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	void run();

private:
	void update();
	void draw();

	void Initialize();

	Clock _clock;

	SDL_Renderer* _renderer;
	SDL_Window* _window;

	std::unique_ptr<ResourceManager> _resourceManager;
	std::unique_ptr<PlayerCharacter> _player;
	std::unique_ptr<PlayerCharacter> _enemy;
	std::unique_ptr<World> _world;

	std::map<SDL_Scancode, bool> _keyboardStatus;

	std::vector<KeyBind> _keyBinds;

	bool _running{ true };
};