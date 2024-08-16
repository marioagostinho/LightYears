#pragma once

#include <widgets/HUD.h>
#include <widgets/TextWidget.h>
#include <widgets/ValueGuage.h>

namespace ly
{
	class Actor;

	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Tick(float deltaTime) override;
		virtual void Draw(sf::RenderWindow& windowRef) override;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;


		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
		void PlayerSpaceshipDestroyed(Actor* Actor);
		void RefreshHealthBar();

		TextWidget mFramerateText;
		ValueGuage mPlayerHealthBar;

		sf::Color mHealthyHealthBarColor;
		sf::Color mCriticialHealthBarColor;
		float mCriticalThreshold;
	};
}