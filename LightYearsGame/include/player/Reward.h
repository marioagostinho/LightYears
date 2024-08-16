#pragma once

#include <functional>
#include <framework/Actor.h>

namespace ly
{
	class World;
	class PlayerSpaceship;

	using RewardFunc = std::function<void(PlayerSpaceship*)>;
	using RewardFactoryFunc = std::function<weak<class Reward>(World*)>;

	class Reward : public Actor
	{
	public:
		Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed = 200.f);

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;

		float mSpeed;
		RewardFunc mRewardFunc;
	};

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc);

	weak<Reward> CreateHealthReward(World* world);
	weak<Reward> CreateThreewayShooterReward(World* world);
	weak<Reward> CreateFrontalWiperReward(World* world);
	weak<Reward> CreateLifeReward(World* world);

	void RewardHealth(PlayerSpaceship* player);
	void RewardThreewayShooter(PlayerSpaceship* player);
	void RewardFrontalWiper(PlayerSpaceship* player);
	void RewardLife(PlayerSpaceship* player);
}