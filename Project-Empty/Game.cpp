#include <iostream>
#include <string>
#include <format>

#include "Game.h"
#include "Config.h"
#include "Strings.h"

void Game::game
{
	while (running)
	{
		update();
		draw();
	}
}

void Game::initialize()
{
	running = false

		SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window(nullptr);
	SDL_Renderer* renderer(nullptr);

	SDL_CreateWindowAndRenderer(ProjectName.c_str(), Config::ScreenWidth, Config::ScreenHeight, 0);

	if (window == nullptr)
	{
		std::cerr << "Failed to initialize SDL window\n";
		SDL_Quit();
		return;
	}

	if (renderer == nullptr)
	{
		std::cerr << "Failed to initialize SDL Renderer\n";
		SDL_DestroyWindow(window);
		SDL_Quit;
		return;
	}

	if (!initialize_mixer()) return;

	if (!initialize_ttf()) return;

	SDL_SetRenderVSync(Renderer, 1);

	running = true;

	_Ship.loadTexture(Renderer, "Assets\\Ship.png");

	auto Surface = SDL_LoadPNG("Assets\\Star_Tiny.png");

	if (Surface)
	{
		_BulletTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
		SDL_DestroySurface(Surface);
	}
	else
	{
		std::cerr << "failed to load assets\\Star_Tiny.png";
	}

	for (int i = 0; i < 5; i++)
	{
		_Asteroids.emplace_back(std::make_unique<Asteroids>(Size::Large)):
	}

	for (auto& asteroid : _Asteroids)
	{
		asteroid->loadTexture(Renderer, "Assets\\Meteor_DLarge.png")
	}
}

bool Game::initialize_mixer()
{
	if (!MIX_Init())
	{
		std::cerr << "Failed to initialize SDL_Mixer: " << SDL_GetError();
		return false;
	}

	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

	if (!mixer)
	{
		std::cerr << "Failed to create mixer: " << SDL_GetError();
		return false;
	}

	shotAudio = MIX_LoadAudio(mixer, "Assets\\laserLarge_000.ogg", true);
	if (!shotAudio)
	{
		std::cerr << " Failed to load audio file (Assets\\laserLarge_000.ogg): " << SDL_GetError();
		return false;
	}

	explosionAudio = MIX_LoadAudio(mixer, "Assets\\lowFrequency_explosion_000.ogg", true);
	if (!explosionAudio)
	{
		std::cerr << " Failed to load audio file (Assets\\lowFrequency_explosion_000.ogg): " << SDL_GetError();
		return false;
	}

	shotTrack = MIX_CreateTrack(mixer);
	if (!shotTrack)
	{
		std::cerr << "Failed to create track: " << SDL_GetError();
		return false
	}

	explosionTrack = MIX_CreateTrack(mixer);
	if (!explosionTrack)
	{
		std::cerr << "Failed to create track: " << SDL_GetError();
		return false
	}

	MIX_SetTrackAudio(shotTrack, shotAudio);
	MIX_SetTrackAudio(explosionTrack, explosionAudio);

	return true;
}

//bool Game::initialize_ttf()
//{
//	if (!TTF_Init())
//	{
//		std::cerr << "Failed to initialize TTF: " << SDL_GetError() << '\n';
//		return false
//	}
//
//	_GameFonts = TTF_OpenFront("Assets\\Instruction.otf", 22.0f);
//	if (!_GameFonts)
//	{
//		std::cerr << "Couldn't open font: " << SDL_GetError() << '\n';
//		return false;
//	}
//
//	_MenuFonts = TTF_OpenFront("Assets\\Instruction.otf", 22.0f);
//	if (!_MenuFonts)
//	{
//		std::cerr << "Couldn't open font: " << SDL_GetError() << '\n';
//		return false;
//	}
//
//	for (auto uiText : UI::strings)
//	{
//		SDL_Surface* Surface = TTF_RenderText_Blended(uiText.size == UI::textSize::Menu ? _MenuFont : _GameFont, uiText.str.c_str(), 0, SDL_Color{ 255, 255, 255, SDL_ALPHA_OPAQUE });
//		if (Surface)
//		{
//			_StaticText[uiText.str] = SDL_CreateTextureFromSurface(Renderer, Surface);
//			SDL_DestroySurface(Surface);
//		}
//	}
//
//	return true;
//}

Uint32 controlFire(void* data, SDL_TimerIDD TimerID, Uint32 Interval)
{
	auto ship = static_cast<Ship*>(data);
	ship->allowFire();

	return 0;
}

Uint32 destroyBullet(void* data, SDL_TimerIDD TimerID, Uint32 Interval)
{
	auto bullet = static_cast<Ship*>(data);
	bullet->flagForRemoval();

	return 0;
}

void Game::update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EventType::SDL_EVENT_QUIT)
		{
			running = false;
			break;
		}

		if (event.type == SDL_EventType::SDL_EVENT_KEY_DOWN)
		{
			if (event.key.key == SDLK_ESCAPE) running = false;
			if (event.key.key == SDLK_W) _Ship.startAccelerating();
			if (event.key.key == SDLK_A) isAPressed = true;
			if (event.key.key == SDLK_D) isDPressed = true;
			if (event.key.key == SDLK_SPACE) isSPACEPressed = true;
		}

		if (event.type == SDL_EventType::SDL_EVENT_KEY_UP)
		{
			if (event.key.key == SDLK_W) _Ship.stopAccelerating();
			if (event.key.key == SDLK_A) isAPressed = false;
			if (event.key.key == SDLK_D) isDPressed = false;
			if (event.key.key == SDLK_SPACE) isSPACEPressed = false;
		}
	}

	if (_RotateLeft)
	{
		_Ship.rotate(RotationDir::Left);
	}

	if (_RotateRight)
	{
		_Ship.rotate(RotationDir::Right);
	}

	if (_firing && _Ship.canFire())
	{
		_Ship.fire();
		SDL_AddTimer(Config::FireRate, controlFire, &_Ship);
		auto shipPos = _Ship.getPosition();
		_Bullets.emplace_back(std::make_unique<Bullet>(shipPos, _Ship.getAngle()));
		_Bullets.back()->setTexture(_BulletTexture);
		MIX_PlayTrack(shotTrack, 0);
		SDL_AddTimer(Config::BulletLife, destroyBullet, _Bullets.back().get());
	}

	_Ship.update();

	for (auto& asteroid : _Asteroids)
	{
		asteroid->update();
	}

	std::vector<Asteroid*> destroyedAsteroids;

	for (auto& bullet : _Bullets)
	{
		if (bullet->shouldRemove()) continue;


		for (auto& asteroid : _asteroids)
		{
			if (asteroid->shouldRemove()) continue;
			auto bulletPos = Bullet->getPosition();
			auto asteroidPos = asteroid->getPosition();
			Vector2 diff{ bulletPos.x - asteroidPos.x, bulletPos.y - roidPos.y };
			auto dist = diff.magnitude();

			if (dist <= bullet->getRadius() + asteroid->getRadius())
			{
				bullet->flagForRemoval();
				asteroid->flagForRemoval();

				MIX_PlayTrack(explosionTrack, 0);

				if (asteroid->getSize() == Size::Large)
				{
					destroyedAsteroids.push_back(asteroid.get());
				}
			}
		}
	}

	for (aut& asteroid : destroyedAsteroids)
	{
		auto& one = _Asteroids.emolace_back(std::make_unique<Asteroid>(asteroid->getPosition(), Size::Small));
		one->loadTexture(Renderer, "Assets\\Meteor_DSmall.png");
		auto& two = _Asteroids.emolace_back(std::make_unique<Asteroid>(asteroid->getPosition(), Size::Small));
		two->loadTexture(Renderer, "Assets\\Meteor_DSmall.png");
	}

	std::erase_if(_Bullets, [](const std::unique_ptr<Bullet>& b) {return b->shouldRemove(); });
	std::erase_if(_Asteroids, [](const std::unique_ptr<Asteroids>& a) {return a->shouldRemove(); });

	if (_Asteroids.empty())
	{
		// Game Over
	}
}

void Game::drawUI()
{
	SDL_FRect scoreRect{ 10.0f, 10.0f, _staticText["score"]->w, _staticText["score"]->h };
	SDL_RenderTexture(Renderer, _staticText["score"], NULL, &scoreRect);

	SDL_FRect liveRect{ Config::ScrenWidth - 110 - _staticText["lives"]->w, 10.0f, _staticText["lives"]->w, _staticText["lives"]->h };
	SDL_RenderTexture(Renderer, _staticText["lives"], NULL, &liveRect);
}

void Game::draw()
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);

	_Ship.draw(Renderer);
	for (auto& asteroid : _Asteroids)
	{
		asteroid->draw(renderer);
	}

	for (auto& bullet : _Bullets)
	{
		bullet->draw(Renderer);
	}

	drawUI();

	SDL_RenderPresent(Renderer);
}