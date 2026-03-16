#pragma once

#include "GameObject.h"
#include "Vector2.h"

class Bullet : public GameObject
{
public:
	Bullet(Vector2& pos, float angle);
	~Bullet()
	{
		_Texture = nullptr;
	}
};