#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Object.h"

namespace ly 
{
	class Widget : public Object
	{
	public:
		void NativeDraw(sf::RenderWindow& windowRef);
		virtual bool HandleEvent(const sf::Event& event);

		void SetWidgetLocation(const sf::Vector2f& newLocation);
		void SetWidgetRotation(float newRotation);
		void SetVisibility(bool newVisibility);

		sf::Vector2f GetWidgetLocation() const { return mWidgetTransform.getPosition(); }
		float GetWidgetRotation() const { return mWidgetTransform.getRotation(); }
		bool GetVisibility() const { return mIsVisible; }

	protected:
		Widget();

	private:
		virtual void Draw(sf::RenderWindow& windowRef);
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);

		sf::Transformable mWidgetTransform;
		bool mIsVisible;
	};
}