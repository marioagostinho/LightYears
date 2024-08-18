#pragma once

#include <framework/TimerManager.h>

#include "spaceship/Spaceship.h"

namespace ly
{
	class Shooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

		void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
		float GetSpeed() const { return mSpeed; }

		void SetShooter(unique<Shooter>&& newShooter);

		virtual void Shoot() override;
		virtual void ApplyDamage(float amt) override;

	private:
		void HandleInput();
		void NormalizeInput();
		void ClampInputOnEdge();
		void ConsumeInput(float deltaTime);;

		void UpdateInvunerable(float deltaTime);
		void StopInvulnerable();

		sf::Vector2f mMoveInput;
		float mSpeed;

		unique<Shooter> mShooter;

		float mInvulnerableTime;
		TimerHandle mInvulnerableTimerHandle;
		bool mInvulnerable;

		float mInvulnerableFlashInterval;
		float mInvulnerableFlashTimer;
		float mInvulnerableFlashDir;
	};
}