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

		if (amt < 0)
		{
			TakenDamage(-amt);

			if (mHealth <= 0)
			{
				HealthEmpty();
			}
		}
		else
		{
			HealthRegen(amt);
		}
	}

	void HealthComponent::TakenDamage(float amt)
	{
		LOG("Took damage(%f): %f/%f", amt, mHealth, mMaxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		LOG("Dead");
	}

	void HealthComponent::HealthRegen(float amt)
	{
		LOG("Health regen(%f): %f/%f", amt, mHealth, mMaxHealth);
	}
}