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
		actorToDestroy.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		actorToDestroy.lock()->SetActorRotation(90.f);
		counter = 0.f;
	}

	// Test
	void GameApplication::Tick(float deltaTime)
	{
	}
}