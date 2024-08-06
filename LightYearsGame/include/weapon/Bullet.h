#pragma once

#include <framework/Actor.h>
#include <framework/Core.h>

namespace ly
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 600.f, float damage = 10.f);

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

		inline void SetSpeed(float newSpeed) { mSpeed = newSpeed; };
		inline void SetDamage(float newDamage) { mDamage = newDamage; };

		float GetDamage() const { return mDamage; }

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;

		void Move(float deltaTime);

		Actor* mOwner;
		float mSpeed;
		float mDamage;
	};
}