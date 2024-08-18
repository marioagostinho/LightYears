#pragma once

#include "spaceship/Spaceship.h"
#include "player/Reward.h"

namespace ly
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld,
			const std::string& texturePath,
			float collisionDamage = 200.f,
			float rewardSpawnWeight = 0.5f,
			const List<RewardFactoryFunc> rewards =
			{
				CreateHealthReward,
				CreateThreewayShooterReward,
				CreateFrontalWiperReward,
				CreateLifeReward
			});

		virtual void Tick(float deltaTime) override;
		void SetScoreAwardAmt(unsigned int amt);
		void SetRewardSpawnWeigh(float weight);
	private:
		void SpawnReward();

		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;

		float mCollisionDamage;
		unsigned int mScoreAwardAmt;
		float mRewardSpawnWeight;

		List<RewardFactoryFunc> mRewardFactories;
	};
}