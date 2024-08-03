#include <framework/Core.h>

#include "framework/Application.h"
#include "framework/World.h"

namespace ly 
{
	Application::Application()
		: mWindow(sf::VideoMode(1024, 1440), "Light Years"),
		mTargetFrameRate(60.f),
		mTickClock(),
		currentWorld(nullptr)
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

		if (currentWorld)
		{
			currentWorld->TickInternal(deltaTime);
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
		sf::CircleShape rect(50);
		rect.setFillColor(sf::Color::Green);
		rect.setOrigin(50, 50);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);

		mWindow.draw(rect);
	}
}