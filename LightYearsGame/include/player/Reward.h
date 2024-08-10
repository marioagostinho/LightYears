#pragma once

#include <functional>
#include <framework/Actor.h>

namespace ly
{
	using RewardFunc = std::function<void(PlayerSpaceship*)>;
	using RewardFactoryFunc = std::function<weak<class Reward>(World*)>;

	class World;
	class PlayerSpaceship;
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

	void RewardHealth(PlayerSpaceship* player);
	void RewardThreewayShooter(PlayerSpaceship* player);
	void RewardFrontalWiper(PlayerSpaceship* player);
}