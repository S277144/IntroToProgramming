#include "Animated_Object.h"

void AnimatedObject::update(float dt)
{
	_nextFrame -= dt;

	if (_nextFrame <= 0.0f)
	{
		_nextFrame = _frameLength;

		_currentFrame++;

		if (_currentFrame >= _animations[_currentAnimation].frame.size()) _currentFrame = 0;

		_animRect = _animations[_currentAnimation].frame[_currentFrame];
	}

	GameObject::update(dt);
}

void AnimatedObject::draw(SDL_Renderer* renderer)
{
	SDL_FRect srcRect = _animations[_currentAnimation].frame[_currentFrame];
	SDL_Texture* texture = _animations[_currentAnimation].texture;
	SDL_FRect dst
	{
		.x = _position.x,
		.y = _position.y,
		.w = Config::AnimFrameWidth * Config::RenderScale,
		.h = Config::AnimFrameHeight * Config::RenderScale,
	};

	SDL_RenderTextureRotated(renderer, _animations[_currentAnimation].texture, &srcRect, &dst, 0.0, NULL, _direction == Direction::Left ? SDL_FlipMode::SDL_FLIP_HORIZONTAL : SDL_FlipMode::SDL_FLIP_NONE);
}

void AnimatedObject::setAnimation(const std::string& name)
{
	if (_animations.contains(name))
	{
		_currentAnimation = name;

		_currentFrame = 0;
		_frameLength = 1.0 / _animations[name].frameRate;
		_nextFrame = _frameLength;
	}
}

void AnimatedObject::addAnimation(const std::string & name, SDL_Texture * tex, const std::vector<SDL_FRect>&frames, int frameRate)
{
	_animations[name] = 
	{
		.texture = tex,
		.frame = frames,
		.frameRate = frameRate
	};
}

SDL_FRect AnimatedObject::getRect() const
{
	return SDL_FRect
	{
		.x = _position.x,
		.y = _position.y,
		.w = Config::AnimFrameWidth,
		.h = Config::AnimFrameHeight
	};
}
