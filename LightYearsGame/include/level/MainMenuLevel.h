#pragma once

#include <framework/World.h>

namespace ly
{
	class MainMenuHUD;

	class MainMenuLevel : public World
	{
	public:
		MainMenuLevel(Application* owningApp);

		virtual void BeginPlay() override;

	private:
		void StartGame();
		void QuitGame();

		weak<MainMenuHUD> mMainMenuHUD;
	};
}