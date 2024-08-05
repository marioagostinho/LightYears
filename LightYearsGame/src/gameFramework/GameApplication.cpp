#include <framework/World.h>
#include <framework/AssetManager.h>

#include "config.h"
#include "player/PlayerSpaceship.h"
#include "Spaceship/Spaceship.h"
#include "gameFramework/GameApplication.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication();
}

namespace ly
{
	GameApplication::GameApplication()
		: Application(600, 980, "Light Years", sf::Style::Titlebar || sf::Style::Close)
	{
		// Asset manager
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());

		// World
		weak<World> newWorld = LoadWorld<World>();

		// Test
		testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Spaceship> testSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
		testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
		testSpaceship.lock()->SetActorLocation(sf::Vector2f(100.f, 50.f));

		counter = 0;
	}

	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;

		if (counter >= 10.f)
		{
			if (!testPlayerSpaceship.expired())
			{
				testPlayerSpaceship.lock()->Destroy();
			}
		}
	}
}