#include <gameplay/WaitStage.h>

#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/HexagonStage.h"
#include "enemy/UFOStage.h"

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
	}

	void GameLevelOne::BeginPlay()
	{
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));
		AddStage(shared<VanguardStage>(new VanguardStage(this)));

		AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));
		AddStage(shared<TwinBladeStage>(new TwinBladeStage(this)));

		AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));
		AddStage(shared<HexagonStage>(new HexagonStage(this)));

		AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));
		AddStage(shared<UFOStage>(new UFOStage(this)));
	}
}