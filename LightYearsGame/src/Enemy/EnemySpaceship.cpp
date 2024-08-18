#include <framework/MathUtility.h>

#include "player/PlayerManager.h"
#include "Enemy/EnemySpaceship.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* owningWorld,
		const std::string& texturePath,
		float collisionDamage,
		float rewardSpawnWeight,
		const List<RewardFactoryFunc> rewards)
		: Spaceship(owningWorld, texturePath),
		mCollisionDamage(collisionDamage),
		mRewardFactories(rewards),
		mScoreAwardAmt(10),
		mRewardSpawnWeight(rewardSpawnWeight)
	{
		SetTeamID(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f))
		{
			Destroy();
		}
	}

	void EnemySpaceship::SetScoreAwardAmt(unsigned int amt)
	{
		mScoreAwardAmt = amt;
	}

	void EnemySpaceship::SetRewardSpawnWeigh(float weight)
	{
		if (weight < 0.f || weight > 1.f)
			return;

		mRewardSpawnWeight = weight;
	}

	void EnemySpaceship::SpawnReward()
	{
		if (mRewardFactories.size() == 0 || mRewardSpawnWeight < RandomRange(0, 1))
			return;

		int pick = (int)RandomRange(0, mRewardFactories.size());

		if (pick >= 0 && pick < mRewardFactories.size())
		{
			weak<Reward> newReward = mRewardFactories[pick](GetWorld());
			newReward.lock()->SetActorLocation(GetActorLocation());
		}
	}

	void EnemySpaceship::OnActorBeginOverlap(Actor* other)
	{
		Spaceship::OnActorBeginOverlap(other);

		if (IsOtherHostile(other))
		{
			other->ApplyDamage(mCollisionDamage);
		}
	}

	void EnemySpaceship::Blew()
	{
		SpawnReward();

		if (Player* player = PlayerManager::Get().GetPlayer())
		{
			player->AddScore(mScoreAwardAmt);
		}
	}
}