#include "framework/AssetManager.h"
#include "widgets/ValueGuage.h"

namespace ly
{
	ValueGuage::ValueGuage(const sf::Vector2f& size, 
		float initualPercent, 
		const sf::Color& foregroundColor, 
		const sf::Color& backgroundColor)
		: mTextFont(AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")),
		mText("", *(mTextFont.get())),
		mBarFont(size),
		mBarBack(size),
		mPercent(initualPercent),
		mForegroundColor(foregroundColor),
		mBackgroundColor(backgroundColor)
	{
		mBarFont.setFillColor(mForegroundColor);
		mBarBack.setFillColor(mBackgroundColor);
		SetTextSize(20);
	}

	void ValueGuage::UpdateValue(float value, float maxValue)
	{
		if (maxValue == 0)
			return;

		mPercent = value / maxValue;
		std::string displayStr = std::to_string((int)value) + "/" + std::to_string((int)maxValue);
		mText.setString(displayStr);

		sf::Vector2f barSize = mBarBack.getSize();
		mBarFont.setSize({ barSize.x * mPercent, barSize.y });
		CenterText();
	}

	sf::FloatRect ValueGuage::GetBound() const
	{
		return mBarBack.getGlobalBounds();
	}

	void ValueGuage::SetTextSize(unsigned int characterSize)
	{
		mText.setCharacterSize(characterSize);
	}

	void ValueGuage::SetForegroundColor(const sf::Color& color)
	{
		mBarFont.setFillColor(color);
	}

	void ValueGuage::SetBackgroundColor(const sf::Color& color)
	{
		mBarBack.setFillColor(color);
	}

	void ValueGuage::LocationUpdated(const sf::Vector2f& newLocation)
	{
		mBarFont.setPosition(newLocation);
		mBarBack.setPosition(newLocation);

		CenterText();
	}

	void ValueGuage::RotationUpdated(float newRotation)
	{
		mText.setRotation(newRotation);
		mBarFont.setRotation(newRotation);
		mBarBack.setRotation(newRotation);
	}

	void ValueGuage::CenterText()
	{
		sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBound = mText.getGlobalBounds();
		mText.setPosition(widgetCenter - sf::Vector2f{textBound.width /2.f, textBound.height});
	}

	void ValueGuage::Draw(sf::RenderWindow& windowRef)
	{
			windowRef.draw(mBarBack);
			windowRef.draw(mBarFont);
			windowRef.draw(mText);
	}
}