#pragma once

#include <widgets/HUD.h>
#include <widgets/TextWidget.h>
#include <widgets/Button.h>

namespace ly
{
	class MainMenuHUD : public HUD
	{
	public:
		MainMenuHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual bool HandleEvent(const sf::Event& event) override;

		Delegate<> onStartButtonClicked;
		Delegate<> onQuintButtonClicked;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;

		void StartButtonClicked();
		void QuitButtonClicked();

		TextWidget mTitleText;
		Button mStartButton;
		Button mQuitButton;
	};
}
