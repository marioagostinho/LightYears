#pragma once

#include "framework/Delegate.h"

namespace ly
{
	class HealthComponent
	{
	public:
		HealthComponent(float health, float maxHealth);

		void ChangeHealth(float amt);

		void SetInitialHealth(float health, float maxHealth);

		float GetHealth() const { return mHealth; }
		float GetMaxHealth() const { return mMaxHealth; }

		Delegate<float, float, float> onHealthChanged;
		Delegate<float, float, float> onTakenDamage;
		Delegate<> onHealthEmpty;

	private:
		void TakenDamage(float amt);
		void HealthEmpty();

		float mHealth;
		float mMaxHealth;
	};
}