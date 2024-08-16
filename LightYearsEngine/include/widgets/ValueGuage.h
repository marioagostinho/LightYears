#pragma once

#include "widgets/Widget.h"

namespace ly
{
	class ValueGuage : public Widget
	{
	public:
		ValueGuage(const sf::Vector2f& size = { 200.f, 30.f }, 
			float initualPercent = 0.75,
			const sf::Color& foregroundColor = sf::Color(128, 255, 128, 255),
			const sf::Color& backgroundColor = sf::Color(128, 128, 128, 255));

		void UpdateValue(float value, float maxValue);
		virtual sf::FloatRect GetBound() const override;

		void SetTextSize(unsigned int characterSize);

		void SetForegroundColor(const sf::Color& color);
		void SetBackgroundColor(const sf::Color& color);
	private:
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;
		void CenterText();
		virtual void Draw(sf::RenderWindow& windowRef) override;

		shared<sf::Font> mTextFont;
		sf::Text mText;

		sf::RectangleShape mBarFont;
		sf::RectangleShape mBarBack;

		sf::Color mForegroundColor;
		sf::Color mBackgroundColor;

		float mPercent;
	};
}