#include <framework/MathUtility.h>

#include "VFX/Explosion.h"
#include "spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor(owningWorld, texturePath),
		mVelocity(),
		mHealthComp(100.f, 100.f),
		mBlinkTime(0.f),
		mBlickDuration(0.2f),
		mBlinkColorOffset(255, 0, 0, 255)
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
		UpdateBlink(deltaTime);
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

	void Spaceship::Blink()
	{
		if (mBlinkTime == 0.f)
		{
			mBlinkTime = mBlickDuration;
		}
	}

	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (mBlinkTime > 0.f)
		{
			mBlinkTime -= deltaTime;
			mBlinkTime = mBlinkTime > 0.f ? mBlinkTime : 0.f;

   			GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
		}
	}

	void Spaceship::OnHealtChanged(float amt, float health, float maxHealth)
	{
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{
		Blink();
	}

	void Spaceship::Blow()
	{
		Explosion* exp = new Explosion();
		exp->SpawnExplosion(GetWorld(), GetActorLocation());

		Destroy();
		delete exp;
	}
}