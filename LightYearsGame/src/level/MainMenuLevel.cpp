#include <framework/Application.h>

#include "level/GameLevelOne.h"
#include "widgets/MainMenuHUD.h"
#include "level/MainMenuLevel.h"

namespace ly
{
	MainMenuLevel::MainMenuLevel(Application* owningApp)
		: World(owningApp)
	{
		mMainMenuHUD = SpawnHUD<MainMenuHUD>();
	}

	void MainMenuLevel::BeginPlay()
	{
		mMainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
		mMainMenuHUD.lock()->onQuintButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);
	}

	void MainMenuLevel::StartGame()
	{
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void MainMenuLevel::QuitGame()
	{
		GetApplication()->QuitApplication();
	}
}