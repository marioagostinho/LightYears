#include <framework/World.h>
#include <framework/AssetManager.h>

#include "config.h"
#include "player/PlayerSpaceship.h"
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

		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();

		// Test
		testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testPlayerSpaceship.lock()->SetActorRotation(0.f);
	}

	void GameApplication::Tick(float deltaTime)
	{
	}
}