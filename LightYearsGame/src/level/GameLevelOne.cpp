#include <gameplay/WaitStage.h>

#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/HexagonStage.h"
#include "enemy/UFOStage.h"
#include "enemy/ChaosStage.h"
#include "player/PlayerManager.h"
#include "widgets/GameplayHUD.h"

#include "level/GameLevelOne.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World(owningApp)
	{
	}

	void GameLevelOne::BeginPlay()
	{
		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);

		mGameplayHUD = SpawnHUD<GameplayHUD>();
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

		AddStage(shared<WaitStage>(new WaitStage(this, 5.f)));
		AddStage(shared<ChaosStage>(new ChaosStage(this)));
	}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
	{
		mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);

		if (!mPlayerSpaceship.expired())
		{
			mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::GameOver()
	{
		LOG("GAME OVER MATE!");
	}
}