#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Object.h"

namespace ly
{
	class HUD : public Object
	{
	public:
		virtual void Tick(float deltaTime);

		virtual void Draw(sf::RenderWindow& windowRef) = 0;
		void NativeInit(const sf::RenderWindow& windowRef);
		virtual bool HandleEvent(const sf::Event& event);

		bool HasInit() { return mAlreadyInit; }
	protected:
		HUD();

	private:
		virtual void Init(const sf::RenderWindow& windowRef);

		bool mAlreadyInit;
	};
}