#pragma once

#include <SDL3/SDL.h>
#include <map>
#include <string>
#include <vector>

#include "Config.h"
#include "Resource_Manager.h"

enum class TileType
{
	Sky,
	LeftGround,
	MidGround,
	RightGround
};

struct Tile
{
	int x;
	int y;
	TileType type;
};

class World
{
public:
	World(ResourceManager* resMan) : _resourceManager{ resMan } 
	{
		loadLevelFile("assets\\levels\\1.txt");

		_worldTexture = _resourceManager->getTexture("World");

		_tileRectMap[TileType::LeftGround] = SDL_FRect{ 4.0f * 65.0f, 11.0f * 65.0f, 64.0f, 64.0f};
		_tileRectMap[TileType::MidGround] = SDL_FRect{ 3.0f * 65.0f, 11.0f * 65.0f, 64.0f, 64.0f };
		_tileRectMap[TileType::RightGround] = SDL_FRect{ 5.0f * 65.0f, 11.0f * 65.0f, 64.0f, 64.0f };
	}

	void draw(SDL_Renderer* renderer);

	SDL_FRect check_collisions(const SDL_FRect& path);

private:

	void loadLevelFile(const std::string& path);

	std::vector<Tile> _worldTiles;
	ResourceManager* _resourceManager;
	SDL_Texture* _worldTexture;
	std::map<TileType, SDL_FRect> _tileRectMap;
};