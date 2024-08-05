#pragma once

#include <framework/Actor.h>

namespace ly
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 600.f, float damage = 10.f);

		inline void SetSpeed(float newSpeed) { mSpeed = newSpeed; };
		inline void SetDamage(float newDamage) { mDamage = newDamage; };

		virtual void Tick(float deltaTime) override;

	private:
		void Move(float deltaTime);

		Actor* mOwner;
		float mSpeed;
		float mDamage;
	};
}