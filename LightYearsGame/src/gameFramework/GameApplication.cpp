#include <framework/AssetManager.h>

#include "config.h"
#include "level/GameLevelOne.h"
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
		weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();
	}
}