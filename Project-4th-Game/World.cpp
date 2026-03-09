#include <fstream>
#include "world.h"

void World::draw(SDL_Renderer* renderer)
{
	for (auto& tile : _worldTiles)
	{
		if (tile.type == TileType::sky) continue;
		auto srcRect = _tileRectMap[tile.type];
		SDL_FRect dstRect{ tile.x * Config::TileWidth, tile.y * Config::TileHeight, Config::TileWidth, Config::TileHeight };
		SDL_RenderTexture(renderer, _worldTexture, &srcRect, &dstRect);
	}


}