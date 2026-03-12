#include <fstream>
#include "World.h"
#include "Player_Character.h"


void World::draw(SDL_Renderer* renderer)
{
	for (auto& tile : _worldTiles)
	{
		if (tile.type == TileType::Sky) continue;
		auto srcRect = _tileRectMap[tile.type];
		SDL_FRect dstRect{ tile.x * Config::TileWidth, tile.y * Config::TileHeight, Config::TileWidth, Config::TileHeight };
		SDL_RenderTexture(renderer, _worldTexture, &srcRect, &dstRect);
	}
}

SDL_FRect World::check_collisions(const SDL_FRect & dynamic)
{
	SDL_FRect overlap_rect{ 0.0f, 0.0f, 0.0f, 0.0f };

	for (const auto& tile : _worldTiles)
	{
		if (tile.type == TileType::Sky) continue;

		if ( tile.y < dynamic.y)
		{
			auto tileRect = SDL_FRect{ tile.x * Config::TileWidth, tile.y * Config::TileHeight, Config::TileWidth, Config::TileHeight };

			if (SDL_GetRectIntersectionFloat(&dynamic, &tileRect, &overlap_rect))
				break;
		}
	}

	return overlap_rect;
}
	
void World::loadLevelFile(const std::string& path)
{
	std::ifstream file(path);

	int x{ 0 };
	int y{ 0 };

	char ch;

	while (!file.eof())
	{
		file.get(ch);
		switch (ch)
		{
		case '0':
			_worldTiles.emplace_back(x, y, TileType::Sky);
			break;
		case '1':
			_worldTiles.emplace_back(x, y, TileType::LeftGround);
			break;
		case '2':
			_worldTiles.emplace_back(x, y, TileType::MidGround);
			break;
		case '3':
			_worldTiles.emplace_back(x, y, TileType::RightGround);
			break;
		case '\n':
			x = -1;
			y++;
			break;
		default:
			x--;
			break;
		}
		x++;
	}
}