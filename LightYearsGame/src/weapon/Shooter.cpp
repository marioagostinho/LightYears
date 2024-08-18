#include "weapon/Shooter.h"

namespace ly
{
	Shooter::Shooter(Actor* owner)
		: mOwner(owner),
		mCurrentLevel(1),
		mMaxLevel(4)
	{
	}

	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
		{
			ShootImpl();
		}
	}

	void Shooter::IncrementLevel(int amt)
	{
		if (mCurrentLevel == mMaxLevel)
			return;

		++mCurrentLevel;
	}

	void Shooter::SetCurrentLevel(int level)
	{
		mCurrentLevel = level;
	}
}