#pragma once

#include <string>
#include <unordered_map>
#include <Vector>

#include "Config.h"
#include "Game_Object.h"

enum class Direction
{
	Left,
	Right
};

struct Animation
{
	SDL_Texture* texture{ nullptr };
	std::vector<SDL_FRect> frame{};
	int frameRate{ 12 };
};

class AnimatedObject : public GameObject
{
public:
	AnimatedObject() = default;
	AnimatedObject(float x, float y) : GameObject(x, y) {}
	AnimatedObject(const Vector2& position) : GameObject(position) {}

	virtual void update(float dt) override;
	virtual void draw(SDL_Renderer* renderer) override;

	void setAnimation(const std::string& name);

	void addAnimation(const std::string& name, SDL_Texture* tex, const std::vector<SDL_FRect>& frame, int frameRate = 12);

	SDL_FRect getRect() const override;

protected:
	Direction _direction{ Direction::Right };
	int _currentFrame{ 0 };
	float _frameTime{ 0.0f };
	float _nextFrame{ 0.0f };
	float _frameLength{ 0.0f };
	SDL_FRect _animRect{ 0.0f, 0.0f, Config::AnimFrameWidth, Config::AnimFrameHeight };
	std::string _currentAnimation;
	std::unordered_map<std::string, Animation> _animations;
};
