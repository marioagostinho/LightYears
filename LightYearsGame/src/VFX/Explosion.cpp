#include <framework/World.h>
#include <framework/MathUtility.h>
#include <VFX/Particle.h>

#include "VFX/Explosion.h"

namespace ly
{
	Explosion::Explosion(int particleAmt,
		float lifeTimeMin, float lifeTimeMax,
		float sizeMin, float sizeMax,
		float speedMin, float speedMax,
		const sf::Color& particleColor,
		const List<std::string>& particleImagePaths)
		: mParticleAmt(particleAmt),
		mLifeTimeMin(lifeTimeMin), mLifeTimeMax(lifeTimeMax),
		mSizeMin(sizeMin), mSizeMax(sizeMax),
		mSpeedMin(speedMin), mSpeedMax(speedMax),
		mParticleColor(particleColor),
		mParticleImagePaths(particleImagePaths)
	{
	}

	void Explosion::SpawnExplosion(World* world, const sf::Vector2f& location)
	{
		for (int i = 0; i < mParticleAmt; ++i)
		{
			std::string particleImagePath = mParticleImagePaths[(int)RandomRange(0, mParticleImagePaths.size())];
			weak<Particle> newParticle = world->SpawnActor<Particle>(particleImagePath);

			newParticle.lock()->SetActorLocation(location);
			newParticle.lock()->RandomLifeTime(mLifeTimeMin, mLifeTimeMax);
			newParticle.lock()->RandomSize(mSizeMin, mSizeMax);
			newParticle.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
			newParticle.lock()->GetSprite().setColor(mParticleColor);
		}
	}
}