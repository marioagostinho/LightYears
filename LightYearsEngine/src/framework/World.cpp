#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"

namespace ly
{
	World::World(Application* owningApp)
		: mOwningApp(owningApp),
		mBeganPlay(false),
		mActors(),
		mPendingActors(),
		mCurrentStageIndex(-1),
		mGameStages{}
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
			InitGameStages();
			NextGameStage();
		}
	}

	void World::BeginPlay()
	{
		LOG("Begin play");
	}

	void World::TickInternal(float deltaTime)
	{
		// Spawn pending actors
		for (shared<Actor> actor : mPendingActors)
		{
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}

		mPendingActors.clear();

		// Check actors
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			iter->get()->TickInternal(deltaTime);
			++iter;
		}

		// Stages
		if (mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size())
		{
			mGameStages[mCurrentStageIndex]->TickStage(deltaTime);
		}

		Tick(deltaTime);
	}

	void World::Tick(float deltaTime)
	{
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto actor : mActors)
		{
			actor->Render(window);
		}
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return mOwningApp->GetWindowSize();
	}

	void World::CleanCycle()
	{
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if (iter->get()->IsPendingdDestroy())
			{
				iter = mActors.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		for (auto iter = mGameStages.begin(); iter != mGameStages.end();)
		{
			if (iter->get()->IsStageFinished())
			{
				iter = mGameStages.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	void World::AddStage(const shared<GameStage>& newStage)
	{
		mGameStages.push_back(newStage);
	}

	void World::InitGameStages()
	{
	}

	void World::AllGameStageFinished()
	{
	}

	void World::NextGameStage()
	{
		++mCurrentStageIndex;

		if (mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size())
		{
			mGameStages[mCurrentStageIndex]->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
			mGameStages[mCurrentStageIndex]->StartStage();
		}
		else
		{
			AllGameStageFinished();
		}
	}
}