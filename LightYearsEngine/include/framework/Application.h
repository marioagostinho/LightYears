#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
	class World;
	class Application
	{
	public:
		Application();
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

	private:
		void TickInternal(float deltaTime);
		virtual void Tick(float deltaTime);

		void RenderInternal();
		virtual void Render();

		// Window
		sf::RenderWindow mWindow;

		// Frames
		float mTargetFrameRate;
		sf::Clock mTickClock;

		shared<World> currentWorld;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld(new WorldType(this));
		currentWorld = newWorld;
		currentWorld->BeginPlayInternal();

		return newWorld;
	}
}