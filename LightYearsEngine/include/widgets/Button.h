#pragma once

#include "widgets/Widget.h"
#include "framework/Delegate.h"

namespace ly
{
	class Button : public Widget
	{
	public:
		Button(const std::string& textString = "Button",
			const std::string& buttonTexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");

		virtual sf::FloatRect GetBound() const override;
		virtual bool HandleEvent(const sf::Event& windowEvent) override;

		Delegate<> onButtonClicked;

		void SetTextString(const std::string& newStr);
		void SetTextSize(unsigned int characterSize);

	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;

		void CenterText();
		void ButtonUp();
		void ButtonDown();
		void MouseHovered();

		shared<sf::Texture> mButtonTexture;
		sf::Sprite mButtonSprite;

		shared<sf::Font> mButtonFont;
		sf::Text mButtonText;

		sf::Color mButtonDefaultColor;
		sf::Color mButtonDownColor;
		sf::Color mButtonHoverColor;

		bool mIsButtonDown;
	};
}