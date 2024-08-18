#include "weapon/FrontalWiper.h"

namespace ly
{
	FrontalWiper::FrontalWiper(Actor* owner, 
		float cooldownTime, 
		const sf::Vector2f& localOffset,
		float width)
		: Shooter(owner),
		mWidth(width),
		mShooter1(owner, cooldownTime, { localOffset.x, localOffset.y - width / 2.f }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"),
		mShooter2(owner, cooldownTime, { localOffset.x, localOffset.y - width / 6.f }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"),
		mShooter3(owner, cooldownTime, { localOffset.x, localOffset.y + width / 6.f }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"),
		mShooter4(owner, cooldownTime, { localOffset.x, localOffset.y + width / 2.f }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"),
		mShooter5(owner, cooldownTime, { localOffset.x, localOffset.y + width / 1.5f }, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"),
		mShooter6(owner, cooldownTime, { localOffset.x, localOffset.y - width / 1.5f }, -15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png")
	{
	}

	void FrontalWiper::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);

		mShooter1.IncrementLevel(amt);
		mShooter2.IncrementLevel(amt);
		mShooter3.IncrementLevel(amt);
		mShooter4.IncrementLevel(amt);
		mShooter5.IncrementLevel(amt);
		mShooter6.IncrementLevel(amt);
	}

	void FrontalWiper::SetCurrentLevel(int level)
	{
		Shooter::SetCurrentLevel(level);

		mShooter1.IncrementLevel(level);
		mShooter2.IncrementLevel(level);
		mShooter3.IncrementLevel(level);
		mShooter4.IncrementLevel(level);
		mShooter5.IncrementLevel(level);
		mShooter6.IncrementLevel(level);
	}

	void FrontalWiper::ShootImpl()
	{
		mShooter1.Shoot();
		mShooter2.Shoot();
		mShooter3.Shoot();
		mShooter4.Shoot();

		if (GetCurrentLevel() == GetMaxLevel())
		{
			mShooter5.Shoot();
			mShooter6.Shoot();
		}
	}
}