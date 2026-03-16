#include "Asteroids.h"
#include "Util.h"
#include "Config.h"

Asteroid::Asteroid(Size sz) : GameObject(0.0f, 0.0f, 0.0f, sz == Size::Large ? Config::LargeAsteroidRadius : Config::AsteroidRadius), 
_Size{sz}
{
	_Position.x = util::getRandom(1.0f, Config::ScreenWidth);
	_Position.y = util::getRandom(1.0f, Config::ScreenHeight);
	randomiseVelocity();
}

Asteroid::Asteroid(const Vector2& pos, Size sz) : GameObject(pos.x, pos.y, 0.0f, sz == Size::Large ? Config::LargeAsteroidRadius : Config::AsteroidRadius),
_Size{ sz }
{
	randomiseVelocity();
}

void Asteroid::randomiseVelocity()
{
	_Angle = util::getRandom(0.0f, 2.0f * 3.14f);

	_Velocity.x = std::cos(_Angle) * Config::AsteroidSpeed;
	_Velocity.y = std::sin(_Angle) * Config::AsteroidSpeed;
}































































//oink oink i'm a little piggy!!!