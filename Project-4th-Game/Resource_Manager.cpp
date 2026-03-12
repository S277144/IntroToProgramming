#include <iostream>
#include <SDL3\SDL.h>

#include "Resource_Manager.h"

bool ResourceManager::loadTexture(const std::string& name, const std::string& path)
{
	if (_textures.contains(name)) return true;

	if (_renderer == nullptr)
	{
		std::cerr << "Unable to load texture, SDL_Renderer is null\n";
		return false;
	}

	SDL_Surface* surface = SDL_LoadPNG(path.c_str());

	if (!surface)
	{
		std::cerr << "Failed to load texture file (" << path << "): " << SDL_GetError() << '\n';
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);

	if (!texture)
	{
		std::cerr << "Failed to create texture " << SDL_GetError() << '\n';
		return false;
	}

	SDL_DestroySurface(surface);

	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	_textures[name] = texture;
	return true;
}

SDL_Texture* ResourceManager::getTexture(const std::string& name) const
{
	if (!_textures.contains(name)) return nullptr;
	return _textures.at(name);
}