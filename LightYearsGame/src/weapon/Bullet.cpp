#include "weapon/Bullet.h"

namespace ly
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		: Actor(world, texturePath),
		mOwner(owner),
		mSpeed(speed),
		mDamage(damage)
	{
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);
	}

	void Bullet::Move(float deltaTime)
	{
		auto bulletMovement = GetActorForwardDirection() * mSpeed * deltaTime;

		AddActorLocationOffset(bulletMovement);
	}
}