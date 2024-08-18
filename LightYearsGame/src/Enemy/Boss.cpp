#include "gameplay/HealthComponent.h"
#include "enemy/Boss.h"

namespace ly
{
	Boss::Boss(World* world)
		: EnemySpaceship(world, "SpaceShooterRedux/PNG/Enemies/boss.png"),
		mSpeed(100.f),
		mBaseSpeed(100.f),
		mSwitchDistanceToEdge(100.f),
		mBaseShooterLeft(this, 1.f, { 50.f, -50.f}),
		mBaseShooterRight(this, 1.f, { 50.f, 50.f }),
		mThreeWayShooter(this, 4.f, { 100.f, 0.f }),
		mFrontalWiperLeft(this, 5.f, { 80.f, -100.f }),
		mFrontalWiperRight(this, 5.f, { 80.f, 100 }),
		mFinalStageShooterLeft(this, 0.3f, { 50, -150 }),
		mFinalStageShooterRight(this, 0.3f, { 50, 150 }),
		mStage(1)
	{
		SetActorRotation(90.f);
		SetVelocity({ mSpeed, 0.f });
		SetRewardSpawnWeigh(0.f);
	}

	void Boss::BeginPlay()
	{
		EnemySpaceship::BeginPlay();

		HealthComponent& healthComp = GetHealthComp();
		healthComp.SetInitialHealth(3000.f, 3000.f);
		healthComp.onHealthChanged.BindAction(GetWeakRef(), &Boss::HealthChanged);
	}

	void Boss::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		ShootBaseShooters();
		ShootThreeWayShooter();
		ShootFrontalWipers();

		CheckMove();
	}

	void Boss::CheckMove()
	{
		if (GetActorLocation().x > GetWindowSize().x - mSwitchDistanceToEdge)
		{
			SetVelocity({ -mSpeed, 0.f });
		}
		else if (GetActorLocation().x < mSwitchDistanceToEdge)
		{
			SetVelocity({ mSpeed, 0.f });
		}
	}

	void Boss::ShootBaseShooters()
	{
		mBaseShooterLeft.Shoot();
		mBaseShooterRight.Shoot();

		if (mStage == 4)
		{
			mFinalStageShooterLeft.Shoot();
			mFinalStageShooterRight.Shoot();
		}
	}

	void Boss::ShootThreeWayShooter()
	{
		mThreeWayShooter.Shoot();
	}

	void Boss::ShootFrontalWipers()
	{
		mFrontalWiperLeft.Shoot();
		mFrontalWiperRight.Shoot();
	}

	void Boss::HealthChanged(float amt, float health, float maxHealth)
	{
		float percentLeft = health / maxHealth;

		if (percentLeft < 0.7 && percentLeft > 0.5)
		{
			SetStage(2);
		}
		else if (percentLeft < 0.5f && percentLeft > 0.3)
		{
			SetStage(3);
		}
		else if (percentLeft < 0.3)
		{
			SetStage(4);
		}
	}

	void Boss::SetStage(int newStage)
	{
		mStage = newStage;

		mBaseShooterLeft.SetCurrentLevel(mStage);
		mBaseShooterRight.SetCurrentLevel(mStage);
		mThreeWayShooter.SetCurrentLevel(mStage);
		mFrontalWiperLeft.SetCurrentLevel(mStage);
		mFrontalWiperRight.SetCurrentLevel(mStage);

		mSpeed = mBaseSpeed * mStage;
	}
}