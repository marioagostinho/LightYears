#include <framework/World.h>
#include <framework/Actor.h>

#include "config.h"
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
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();

		// Test
		actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		actorToDestroy.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
		counter = 0.f;
	}

	// Test
	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;

		if (counter > 2.f)
		{
			if (!actorToDestroy.expired())
			{
				actorToDestroy.lock()->Destroy();
			}
		}
	}
}