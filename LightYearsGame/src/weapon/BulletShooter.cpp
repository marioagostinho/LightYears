#include <framework/Core.h>
#include <framework/World.h>

#include "weapon/Bullet.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, 
		float cooldownTime, 
		const sf::Vector2f& localPositionOffset, 
		float localRotationOffeset)
		: Shooter(owner),
		mCooldownClock(), 
		mCooldownTime(cooldownTime),
		mLocalPositionOffset(localPositionOffset), 
		mLocalRotationOffset(localRotationOffeset)
	{
	}

	bool BulletShooter::IsOnCooldown() const
	{
		if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
			return false;

		return true;
	}

	void BulletShooter::ShootImpl()
	{
		mCooldownClock.restart();

		sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
		sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();
		
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPositionOffset.x + ownerRightDir * mLocalPositionOffset.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
	}
}