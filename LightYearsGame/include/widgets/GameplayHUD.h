#pragma once

#include <widgets/HUD.h>
#include <widgets/TextWidget.h>
#include <widgets/ValueGuage.h>
#include <widgets/ImageWidget.h>
#include <widgets/Button.h>

namespace ly
{
	class Actor;

	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Tick(float deltaTime) override;
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual bool HandleEvent(const sf::Event& event) override;

		void GameFinished(bool playerWon);

		Delegate<> onRestartBtnClicked;
		Delegate<> onQuitBtnClicked;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;

		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
		void PlayerLifeCountUpdated(int amt);
		void PlayerScoreUpdated(int newScore);
		void PlayerSpaceshipDestroyed(Actor* Actor);

		void RefreshHealthBar();
		void ConnectPlayerStatus();

		void SetHUDVisibility(bool visibility);
		void SetFinalHUDVisibility(bool visibility);
		void RestartButtonClicked();
		void QuitButtonClicked();

		TextWidget mFramerateText;
		ValueGuage mPlayerHealthBar;
		ImageWidget mPlayerLifeIcon;
		TextWidget mPlayerLifeText;
		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		sf::Color mHealthyHealthBarColor;
		sf::Color mCriticialHealthBarColor;
		float mCriticalThreshold;

		float mWidgetSpacing;

		TextWidget mWinLoseText;
		TextWidget mFinalScoreText;
		Button mRestartButton;
		Button mQuitButton;

		sf::Vector2u mWindowSize;
	};
}