#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"
#include "framework/Delegate.h"

class b2Body;

namespace ly
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();

		virtual void Destroy() override;

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
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt);

		// Get location & rotation
		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;

		// Get direction
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;

		sf::FloatRect GetActorGlobalBounds() const;

		// Window
		sf::Vector2u GetWindowSize() const;
		bool IsActorOutOfWindowBounds(float allowance = 10.f) const;

		// World
		const World* GetWorld() const { return mOwningWorld; }
		World* GetWorld() { return mOwningWorld; }

		// Physics
		void SetEnablePhysics(bool enable);
		virtual void OnActorBeginOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);

		// Team
		void SetTeamID(uint8 teamID) { mTeamID = teamID; }

		static uint8 GetNeuralTeamID() { return neutralTeamID; }
		uint8 GetTeamID() const { return mTeamID;  }
		bool IsOtherHostile(Actor* other) const;

		//Damage
		virtual void ApplyDamage(float amt);

		// Sprite
		sf::Sprite& GetSprite() { return mSprite; }
		const sf::Sprite& GetSprite() const { return mSprite; }

		Delegate<Actor*> onActorDestroyed;

	private:
		void CenterPivot();

		// Physics
		void InitializePhysics();
		void UninitializedPhysics();
		void UpdatePhysicsBodyTransform();

		World* mOwningWorld;
		bool mHasBeganPlay;

		// Graphics
		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;

		// Physics
		b2Body* mPhysicsBody;
		bool mPhysicsEnabled;

		uint8 mTeamID;
		const static uint8 neutralTeamID = 255;
	};
}