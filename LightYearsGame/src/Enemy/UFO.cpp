#include "weapon/BulletShooter.h"
#include "enemy/UFO.h"

namespace ly
{
	UFO::UFO(World* owningWorld,
		const sf::Vector2f& velocity,
		const std::string& texturePath, 
		float rotationSpeed)
		: EnemySpaceship (owningWorld, texturePath),
		mShooter1(new BulletShooter(this, .25f, {0.f, 0.f}, -60.f)),
		mShooter2(new BulletShooter(this, .25f, { 0.f, 0.f }, 60.f)),
		mShooter3(new BulletShooter(this, .25f, { 0.f, 0.f }, 180.f)),
		mRotationSpeed(rotationSpeed)
	{
		SetVelocity(velocity);
		SetActorRotation(90.f);
	}

	void UFO::BeginPlay()
	{
		EnemySpaceship::BeginPlay();

		GetHealthComp().SetInitialHealth(80.f, 80.f);
	}

	void UFO::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);

		AddActorRotationOffset(mRotationSpeed * deltaTime);
		Shoot();
	}

	void UFO::Shoot()
	{
		mShooter1->Shoot();
		mShooter2->Shoot();
		mShooter3->Shoot();
	}
}