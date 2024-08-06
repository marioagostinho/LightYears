#include "spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor(owningWorld, texturePath),
		mVelocity(),
		mHealthComp(100.f, 100.f)
	{

	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();

		SetEnablePhysics(true);

		mHealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealtChanged);
		mHealthComp.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
		mHealthComp.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::Blow);
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& newVelocity)
	{
		mVelocity = newVelocity;
	}

	void Spaceship::Shoot()
	{
	}

	void Spaceship::ApplyDamage(float amt)
	{
		mHealthComp.ChangeHealth(-amt);
	}

	void Spaceship::OnHealtChanged(float amt, float health, float maxHealth)
	{
		LOG("Heal changed by: %f, and is now: %f/%f", amt, health, maxHealth);
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{
	}

	void Spaceship::Blow()
	{
		Destroy();
	}
}