#pragma once

#include "vector2.h"
#include <SDL3/SDL.h>
#include <string>

class GameObject
{
public:
	GameObject(float x, float y, float ang, float radius) : _Position{ x ,y }, _Angle{ ang }, _Radius{ radius }, _Texture{ nullptr } {}

	~GameObject()
	{
		if (_Texture)
			SDL_DestroyTexture(_Texture);
	}

	void loadTexture(SDL_Renderer* Renderer, const std::string& path);
	void setTexture(SDL_Texture* Texture);
	void draw(SDL_Renderer* Renderer);
	virtual void update();

	float getX() const { return _Position.x; }
	float getY() const { return _Position.y; }
	Vector2 getPosition() const { return _Position; }

	float getAngle() const { return _Angle; }

	float getradius() const { return _Radius; }

	void flagForRemoval()
	{
		_forRemoval = true;
	}

	bool shouldRemove() const { return _forRemoval; }

protected:

	void screenWrap();

	Vector2 _Position;
	Vector2 _Velocity;
	float _Angle;
	float _Radius;
	SDL_Texture* _Texture;

	bool _forRemoval{ false };
};

