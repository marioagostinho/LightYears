#include <framework/Core.h>

#include "gameplay/HealthComponent.h"

namespace ly
{
	HealthComponent::HealthComponent(float health, float maxHealth)
		: mHealth(health),
		mMaxHealth(maxHealth)
	{
	}

	void HealthComponent::ChangeHealth(float amt)
	{
		if (amt == 0.f || mHealth == 0.f)
			return;

		mHealth += amt;

		if (mHealth < 0.f)
		{
			mHealth = 0.f;
		}
		else if (mHealth > 100.f)
		{
			mHealth = 100.f;
		}

		onHealthChanged.Broadcast(amt, mHealth, mMaxHealth);

		if (amt < 0)
		{
			TakenDamage(-amt);

			if (mHealth <= 0)
			{
				HealthEmpty();
			}
		}
	}

	void HealthComponent::TakenDamage(float amt)
	{
		onTakenDamage.Broadcast(amt, mHealth, mMaxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		onHealthEmpty.Broadcast();
	}
}