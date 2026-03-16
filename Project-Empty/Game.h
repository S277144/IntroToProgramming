#pragma once

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <map>
#include <memory>

#include "Asteroids.h"
#include "Bullet.h"
#include "Config.h"
#include "Ship.h"

class Game
{
public:
	Game() : _ship{ Config::HalfScreenWidth, Config::HalfScreenHeight }
	{
		initialize();
	}

	~Game()
	{
		MIX_Quit();

		SDL_DestroyTexture(_BulletTexture);
		SDL_DestroyRenderer(Renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void run();

private:
	void initialize();
	bool initialize_mixer();
	bool initialize_ttf();

	void update();
	void draw();

	void drawUI();

	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	MIX_Mixer* mixer;
	MIX_Track* shotTrack;
	MIX_Track* explosionTrack;
	MIX_Audio* shotAudio;
	MIX_Audio* explosionAudio;

	TTF_Font* _gameFont;
	TTF_Font* _menuFont;

	Ship _Ship;

	std::map<std::string, SDL_Texture*> _staticText;

	std::vector<std::unique_ptr<Asteroid>> _Asteroids;
	std::vector<std::unique_ptr<Bullet>> _Bulllets;

	SDL_Texture* _BulletTexture;

	bool _RotateLeft{ false };
	bool _RotateRight{ false };

	bool running{ true };
	bool _firing{ false };
	bool _gameOver{ false };
};