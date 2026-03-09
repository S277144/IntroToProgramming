#pragma once

#include <SDL3/SDL.h>
#include <map>
#include <string>

class ResourceManager
{
public:

	ResourceManager(SDL_Renderer* renderer) : _renderer(renderer) {}
	~ResourceManager()
	{
		for (auto& pair : _textures)
		{
			SDL_DestroyTexture(pair.second);
		}
	}

	bool loadTexture(const std::string& name, const std::string& path);
	SDL_Texture* getTexture(const std::string& name) const;

private:
	std::map<std::string, SDL_Texture*> _textures;

	SDL_Renderer* _renderer{ nullptr };
};
