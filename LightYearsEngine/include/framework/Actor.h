#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();

		void BeginPlayInternal();
		virtual void BeginPlay();

		virtual void TickInternal(float deltaTime);
		virtual void Tick(float deltaTime);
		
		void Render(sf::RenderWindow& window);
		void SetTexture(const std::string& texturePath);

		// Set location & rotation
		void SetActorLocation(const sf::Vector2f& newLoc);
		void SetActorRotation(float newRot);

		// Add location & rotation offset
		void AddActorLocationLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt);

		// Get location & rotation
		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;

		// Get direction
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;

	private:
		void CenterPivot();

		World* mOwningWorld;
		bool mHasBeganPlay;

		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;
	};
}