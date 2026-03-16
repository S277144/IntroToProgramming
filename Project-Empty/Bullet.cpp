#include "Bullet.h"
#include "Config.h"

constexpr float MaxSpeed = 3.5f;

Bullet::Bullet(Vector2& pos, float angle) : GameObject{ pos.x, pos.y, angle, Config::BulletRadius }
{
	_Velocity.x = std::cos(_Angle - Config::AngleOffset) * Config::BulletSpeed;
	_Velocity.y = std::sin(_Angle - Config::AngleOffset) * Config::BulletSpeed;
}