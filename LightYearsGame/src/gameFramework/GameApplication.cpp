#include <framework/World.h>
#include <framework/AssetManager.h>

#include "config.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
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

		weak<Vanguard> testSpaceship = newWorld.lock()->SpawnActor<Vanguard>();
		testSpaceship.lock()->SetActorLocation(sf::Vector2f(100.f, 50.f));
	}

	void GameApplication::Tick(float deltaTime)
	{
	}
}