#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"

#include "level/GameLevelOne.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World(owningApp)
	{
		// Test
		testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Vanguard> testSpaceship = SpawnActor<Vanguard>();
		testSpaceship.lock()->SetActorLocation(sf::Vector2f(100.f, 50.f));
	}
}