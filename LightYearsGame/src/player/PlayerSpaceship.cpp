#include <SFML/System.hpp>
#include <framework/MathUtility.h>

#include "weapon/BulletShooter.h"
#include "weapon/FrontalWiper.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		: Spaceship(owningWorld, path),
		mMoveInput(),
		mSpeed(200.f),
		mShooter(new FrontalWiper(this, .1f, { 50.f, 0.f }))
	{
		SetTeamID(1);
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		//Input
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mMoveInput.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mMoveInput.y = 1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			mMoveInput.x = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mMoveInput.x = 1.f;
		}

		ClampInputOnEdge();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
	}

	void PlayerSpaceship::NormalizeInput()
	{
		Normalize(mMoveInput);
	}

	void PlayerSpaceship::ClampInputOnEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();

		if ((actorLocation.x < 0.f && mMoveInput.x == -1)
			|| actorLocation.x > GetWindowSize().x && mMoveInput.x == 1)
		{
			mMoveInput.x = 0.f;
		}

		if ((actorLocation.y < 0.f && mMoveInput.y == -1)
			|| actorLocation.y > GetWindowSize().y && mMoveInput.y == 1)
		{
			mMoveInput.y = 0.f;
		}
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(mMoveInput * mSpeed);
		mMoveInput.x = mMoveInput.y = 0.f;
	}

	void PlayerSpaceship::SetShooter(unique<Shooter>&& newShooter)
	{
		mShooter = std::move(newShooter);
	}

	void PlayerSpaceship::Shoot()
	{
		if (mShooter)
		{
			mShooter->Shoot();
		}
	}
}