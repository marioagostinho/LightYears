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
		mSpeed(250.f),
		mShooter(new BulletShooter(this, .15f, { 50.f, 0.f })),
		mInvulnerableTime(2.f),
		mInvulnerable(true),
		mInvulnerableFlashInterval(0.5),
		mInvulnerableFlashTimer(0.f),
		mInvulnerableFlashDir(1.f)
	{
		SetTeamID(1);
	}

	void PlayerSpaceship::BeginPlay()
	{
		Spaceship::BeginPlay();

		TimerManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceship::StopInvulnerable, mInvulnerableTime);
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		// Input
		HandleInput();
		ConsumeInput(deltaTime);

		// Invunerable
		UpdateInvunerable(deltaTime);
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

	void PlayerSpaceship::UpdateInvunerable(float deltaTime)
	{
		if (!mInvulnerable)
			return;

		mInvulnerableFlashTimer += deltaTime * mInvulnerableFlashDir;

		if (mInvulnerableFlashTimer < 0 || mInvulnerableFlashTimer > mInvulnerableFlashInterval)
		{
			mInvulnerableFlashDir *= -1;
		}

		GetSprite().setColor(LerpColor({ 255, 255, 255, 64 }, { 255, 255, 255, 128 }, mInvulnerableFlashTimer / mInvulnerableFlashInterval));
	}

	void PlayerSpaceship::StopInvulnerable()
	{
		GetSprite().setColor({ 255, 255, 255, 255 });
		mInvulnerable = false;
	}

	void PlayerSpaceship::SetShooter(unique<Shooter>&& newShooter)
	{
		if (mShooter && typeid(*mShooter.get()) == typeid(*newShooter.get()))
		{
			mShooter->IncrementLevel();
		}
		else
		{
			mShooter = std::move(newShooter);
		}
	}

	void PlayerSpaceship::Shoot()
	{
		if (mShooter)
		{
			mShooter->Shoot();
		}
	}

	void PlayerSpaceship::ApplyDamage(float amt)
	{
		if (!mInvulnerable)
		{
			Spaceship::ApplyDamage(amt);
		}
	}
}