#pragma once

#include <SFML/Graphics.hpp>

#include "weapon/BulletShooter.h"

namespace ly
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float cooldownTime = 0.3f, const sf::Vector2f& localOffset = { 0.f, 0.f });

		virtual void IncrementLevel(int amt) override;
		virtual void SetCurrentLevel(int level) override;

	private:
		BulletShooter mShooterLeft;
		BulletShooter mShooterMid;
		BulletShooter mShooterRight;

		BulletShooter mTopLevelShooterLeft;
		BulletShooter mTopLevelShooterRight;

		virtual void ShootImpl() override;
	};
}