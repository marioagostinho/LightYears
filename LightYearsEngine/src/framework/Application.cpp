#include <framework/Core.h>
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"

#include "framework/Application.h"

namespace ly 
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: mWindow(sf::VideoMode(windowWidth, windowHeight), title, style),
		mTargetFrameRate(60.f),
		mTickClock(),
		mCurrentWorld(nullptr),
		mCleanCycleClock(),
		mCleanCycleInterval(2.f)
	{
		
	}

	void Application::Run()
	{
		mTickClock.restart();

		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargetFrameRate;

		while (mWindow.isOpen())
		{
			// Window
			sf::Event windowEvent;

			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					mWindow.close();
				}
				else
				{
					DispatchEvent(windowEvent);
				}
			}

			// Frames
			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;

			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;

				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	// Frames
	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		//Tick
		if (mCurrentWorld)
		{
			mCurrentWorld->TickInternal(deltaTime);
		}

		// Timer
		TimerManager::Get().UpdateTimer(deltaTime);

		//Physics
		PhysicsSystem::Get().Step(deltaTime);

		//Clean cycle
		if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
		{
			mCleanCycleClock.restart();
			AssetManager::Get().CleanCycle();

			if (mCurrentWorld)
			{
				mCurrentWorld->CleanCycle();
			}
		}
	}

	void Application::Tick(float deltaTime)
	{
	}

	// Rendering
	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display();
	}

	void Application::Render()
	{
		if (mCurrentWorld)
		{
			mCurrentWorld->Render(mWindow);
		}
	}

	// Events
	bool Application::DispatchEvent(const sf::Event& event)
	{
		if (mCurrentWorld)
		{
			return mCurrentWorld->DispatchEvent(event);
		}

		return false;
	}
#
	// Window
	sf::Vector2u Application::GetWindowSize() const
	{
		return mWindow.getSize();
	}
}