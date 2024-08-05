#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
	class Actor;
	class World;
	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

		sf::Vector2u GetWindowSize() const;

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
		
		//Clean cycle
		sf::Clock mCleanCycleClock;
		float mCleanCycleInterval;
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