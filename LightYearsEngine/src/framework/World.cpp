#include "framework/World.h"
#include "framework/Core.h"

namespace ly
{
	World::World(Application* owningApp)
		: mOwningApp(owningApp),
		mBeganPlay(false)
	{
	}

	World::~World()
	{
	}

	void World::BeginPlayInternal()
	{
		if (!mBeganPlay)
		{
			mBeganPlay = true;
			BeginPlay();
		}
	}

	void World::BeginPlay()
	{
		LOG("Began play");
	}

	void World::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	void World::Tick(float deltaTime)
	{
		LOG("Tick at frame rate %f", 1.f / deltaTime);
	}
}