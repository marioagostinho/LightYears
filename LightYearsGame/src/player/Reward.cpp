
#include <framework/World.h>

#include "player/PlayerSpaceship.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"
#include "player/Reward.h"

namespace ly
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed)
		: Actor(world, texturePath),
		mRewardFunc(rewardFunc),
		mSpeed(speed)
	{
	}

	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset({ 0.f, mSpeed * deltaTime });
	}

	void Reward::OnActorBeginOverlap(Actor* other)
	{
		PlayerSpaceship* playerSpaceship = static_cast<PlayerSpaceship*>(other);

		if (playerSpaceship != nullptr && !playerSpaceship->IsPendingdDestroy())
		{
			mRewardFunc(playerSpaceship);
		}
	}

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);
		return reward;
	}

	weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth);
	}

	weak<Reward> CreateThreewayShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreewayShooter);
	}

	weak<Reward> CreateFrontalWiperReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter.png", RewardFrontalWiper);
	}

	void RewardHealth(PlayerSpaceship* player)
	{
		static float rewardAmt = 10.f;

		if (player != nullptr && !player->IsPendingdDestroy())
		{
			player->GetHealthComp().ChangeHealth(rewardAmt);
		}
	}

	void RewardThreewayShooter(PlayerSpaceship* player)
	{
		if (player != nullptr && !player->IsPendingdDestroy())
		{
			player->SetShooter(unique<Shooter>(new ThreeWayShooter(player, 0.4, {50.f, 0.f})));
		}
	}

	void RewardFrontalWiper(PlayerSpaceship* player)
	{
		if (player != nullptr && !player->IsPendingdDestroy())
		{
			player->SetShooter(unique<Shooter>(new FrontalWiper(player, 0.4, { 50.f, 0.f })));
		}
	}
}