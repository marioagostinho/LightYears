#pragma once

#include <framework/World.h>
#include <framework/TimerManager.h>

namespace ly
{
	class PlayerSpaceship;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);

	private:
		virtual void BeginPlay() override;

		virtual void InitGameStages() override;
		void PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);
		void GameOver();

		weak<PlayerSpaceship> mPlayerSpaceship;
		TimerHandle timerHandle_Test;
	};
}