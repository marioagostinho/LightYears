#pragma once

#include <framework/Application.h>
#include <framework/Core.h>

namespace ly
{
	class PlayerSpaceship;
	class GameApplication : public Application
	{
	public:
		GameApplication();

		virtual void Tick(float deltaTime) override;

	private:
		weak<PlayerSpaceship> testPlayerSpaceship;

		float counter;
	};
}