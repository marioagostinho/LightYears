#pragma once

#include <SFML/Graphics.hpp>

#include "enemy/EnemySpaceship.h"

namespace ly
{
	class World;
	class BulletShooter;
	class UFO : public EnemySpaceship
	{
	public:
		UFO(World* owningWorld,
			const sf::Vector2f& velocity,
			const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/ufoYellow.png",
			float rotationSpeed = 40.f);

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		
	private:
		virtual void Shoot() override;

		unique<BulletShooter> mShooter1;
		unique<BulletShooter> mShooter2;
		unique<BulletShooter> mShooter3;

		float mRotationSpeed;
	};
}