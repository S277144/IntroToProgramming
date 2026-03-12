#include "Game_Object.h"

void GameObject::alterPosition(float x, float y)
{
	_position.x += x;
	_position.y += y;
}

void GameObject::update(float dt)
{
	if (_static) return;

	_velocity.y += 100.0f * dt;

	_position += _velocity * dt;

	if (_position.y > 540)
	{
		_position.y = 540.0f;
	}
}

void GameObject::draw(SDL_Renderer* renderer)
{
	SDL_FRect dst
	{
		.x = _position.x - _texture->w / 2.0f,
		.y = _position.y - _texture->h / 2.0f,
		.w = static_cast<float>(_texture->w),
		.h = static_cast<float>(_texture->h),
	};

	SDL_RenderTextureRotated(renderer, _texture, NULL, &dst, 0, NULL, SDL_FLIP_NONE);
}

SDL_FRect GameObject::getRect() const
{
	return SDL_FRect
	{
		.x = _position.x - _texture->w / 2.0f,
		.y = _position.y - _texture->h / 2.0f,
		.w = static_cast<float>(_texture->w),
		.h = static_cast<float>(_texture->h),
	};
}