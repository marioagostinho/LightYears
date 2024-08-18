#pragma once

#include "enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"

namespace ly
{
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* world);

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:
		void CheckMove();

		void ShootBaseShooters();
		void ShootThreeWayShooter();
		void ShootFrontalWipers();

		void HealthChanged(float amt, float health, float maxHealth);
		void SetStage(int newStage);

		float mSpeed;
		float mBaseSpeed;
		float mSwitchDistanceToEdge;

		BulletShooter mBaseShooterLeft;
		BulletShooter mBaseShooterRight;
		ThreeWayShooter mThreeWayShooter;
		FrontalWiper mFrontalWiperLeft;
		FrontalWiper mFrontalWiperRight;

		BulletShooter mFinalStageShooterLeft;
		BulletShooter mFinalStageShooterRight;

		int mStage;
	};
}