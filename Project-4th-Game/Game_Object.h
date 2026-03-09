#pragma once

#include <SDL3/SDL_render.h>

#include "Vector2.h"

class GameObject
{
public:
	GameObject() : _position{0.0f, 0.0f}, _texture{nullptr} {}
	GameObject(const Vector2& position) : _position{position}, _texture{ nullptr } {}
	GameObject(const Vector2& position, bool isStatic) : _position{position}, _texture{ nullptr }, _static{ isStatic } {}
	GameObject(float x, float y) : _position{ x, y }, _texture{ nullptr } {}
	GameObject(float x, float y, bool isStatic) : _position{ x, y }, _texture{ nullptr }, _static{ isStatic } {}

	void makestatic() { _static = true; }
	bool isStatic() const { return _static; }

	virtual void update(float dt);
	virtual void draw(SDL_Renderer* renderer);

	virtual SDL_FRect getRect() const;

protected:
	Vector2 _position;
	Vector2 _velocity;
	SDL_Texture* _texture;

	bool _static{ false };
};