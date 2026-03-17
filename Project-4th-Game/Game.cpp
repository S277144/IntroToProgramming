#include <iostream>
#include <functional>

#include "Config.h"
#include "Game.h"

void Game::run()
{
	while (_running)
	{
		update();
		draw();
	}
}

void Game::Initialize()
{
	_running = false;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_CreateWindowAndRenderer(Config::ProjectName.c_str(), Config::ScreenWidth, Config::ScreenHeight, 0, &_window, &_renderer);

	if (_window == nullptr)
	{
		std::cerr << "Failed to initialize SDL window: " << SDL_GetError() << "\n";
		SDL_Quit();
		return;
	}

	if (_renderer == nullptr)
	{
		std::cerr << "Failed to initialize SDL Renderer\n";
		SDL_DestroyWindow(_window);
		SDL_Quit;
		return;
	}

	_resourceManager = std::make_unique<ResourceManager>(_renderer);
	_resourceManager->loadTexture("Player", "assets\\spritesheet-characters-default.png");
	_resourceManager->loadTexture("World", "assets\\spritesheet-tiles-default.png");
	_resourceManager->loadTexture("Coin", "assets\\coin_gold.png");
	_resourceManager->loadTexture("End", "assets\\flag_green_b.png");
	_resourceManager->loadTexture("Enemy", "assets\\snail_walk_a.png");

	SDL_Texture* enemyTexture = _resourceManager->getTexture("Enemy");
	std::make_unique<Enemy>(Config::ScreenWidth / 2.0f, Config::ScreenHeight - 128);
	std::vector<SDL_FRect> walkEFrame = { { Config::AnimFrameWidth, Config::AnimFrameHeight } };

	/*_enemy->addAnimation("walkE", enemyTexture, walkEFrame);

	_enemy->setAnimation("walkE");*/

	SDL_Texture* playerTexture = _resourceManager->getTexture("Player");
	_player = std::make_unique<PlayerCharacter>(Config::ScreenWidth / 2.0f, Config::ScreenHeight - 128);

	std::vector<SDL_FRect> idleFrame = { { 3 * Config::AnimFrameWidth, 0.0f, Config::AnimFrameWidth, Config::AnimFrameHeight } };
	std::vector<SDL_FRect> walkFrame =
	{
		{ 5 * Config::AnimFrameWidth, 0.0f, Config::AnimFrameWidth, Config::AnimFrameHeight },
		{ 0.0f, Config::AnimFrameHeight, Config::AnimFrameWidth, Config::AnimFrameHeight },
		{ Config::AnimFrameWidth, Config::AnimFrameHeight, Config::AnimFrameWidth, Config::AnimFrameHeight }
	};

	std::vector<SDL_FRect> jumpFrame = { { 6 * Config::AnimFrameWidth, 0.0f, Config::AnimFrameWidth, Config::AnimFrameHeight }, };

	_player->addAnimation("idle", playerTexture, idleFrame);
	_player->addAnimation("walk", playerTexture, walkFrame, 6);
	_player->addAnimation("jump", playerTexture, jumpFrame);

	_player->setAnimation("idle");

	_running = true;
	_keyBinds.emplace_back
	(
		SDL_SCANCODE_A, false, Control::Left,
		std::bind(&PlayerCharacter::onReleased, _player.get(), std::placeholders::_1),
		std::bind(&PlayerCharacter::onPressed, _player.get(), std::placeholders::_1)
	);

	_keyBinds.emplace_back
	(
		SDL_SCANCODE_D, false, Control::Right,
		std::bind(&PlayerCharacter::onReleased, _player.get(), std::placeholders::_1),
		std::bind(&PlayerCharacter::onPressed, _player.get(), std::placeholders::_1)
	);

	_keyBinds.emplace_back
	(
		SDL_SCANCODE_SPACE, false, Control::Jump,
		std::bind(&PlayerCharacter::onReleased, _player.get(), std::placeholders::_1),
		std::bind(&PlayerCharacter::onPressed, _player.get(), std::placeholders::_1)
	);

	_world = std::make_unique<World>(_resourceManager.get());
}

void Game::update()
{
	_clock.tick();

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EventType::SDL_EVENT_QUIT)
		{
			_running = false;
			break;
		}

		if (event.type == SDL_EventType::SDL_EVENT_KEY_UP)
		{
			_keyboardStatus[event.key.scancode] = true;
		}

		if (event.type == SDL_EventType::SDL_EVENT_KEY_DOWN)
		{
			_keyboardStatus[event.key.scancode] = false;
		}
	}

	if (_keyboardStatus[SDL_SCANCODE_ESCAPE]) _running = false;

	for (auto& bind : _keyBinds)
	{
		bool keyStatus = _keyboardStatus[bind.key];
		
		if (!bind.isPressed && keyStatus)
		{
			bind.onPress(bind.control);
			bind.isPressed = true;
		}

		if (bind.isPressed && !keyStatus)
		{
			bind.onRelease(bind.control);
			bind.isPressed = false;
		}
	}

	float dt = _clock.delta / 1000.0f;
	_player->update(dt);

	auto overlap = _world->check_collisions(_player->getRect());

	if (overlap.h > 0.0f) 
	{
		_player->alterPosition(0.0f, -overlap.h);
	}

	/*auto overlap = _world->check_collisions(_player->getRect());

	if (overlap.w = TileType::Enemy)
	{
		playerLife = false;
	}*/
}

void Game::draw()
{
	SDL_SetRenderDrawColor(_renderer, 100, 100, 200, 255);
	SDL_RenderClear(_renderer);

	_world->draw(_renderer);

	_player->draw(_renderer);

	SDL_RenderPresent(_renderer);
}