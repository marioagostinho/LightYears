#include <framework/MathUtility.h>
#include <framework/World.h>

#include "enemy/UFO.h"
#include "enemy/UFOStage.h"

namespace ly
{
	UFOStage::UFOStage(World* world)
		: GameStage(world),
		mSpawnInterval(2.f),
		mSpawnAmt(10),
		mCurrentSpawnAmt(0),
		mUFOSpeed(225.f)
	{	
	}

	void UFOStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, mSpawnInterval, true);
	}

	void UFOStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimer);
	}

	sf::Vector2f UFOStage::GetRandomSpawnLoc() const
	{
		auto windowSize = GetWorld()->GetWindowSize();

		float spawnLeft = RandomRange(-1, 1);
		float spawnLocY = RandomRange(0, windowSize.y);
		float spawnLocX = 0;

		spawnLocX = (spawnLeft < 0) ? windowSize.x + 100.f : -100;
		
		return sf::Vector2f{ spawnLocX, spawnLocY };
	}

	void UFOStage::SpawnUFO()
	{
		sf::Vector2f spawnLoc = GetRandomSpawnLoc();
		auto windowSize = GetWorld()->GetWindowSize();
		sf::Vector2f center{ windowSize.x / 2.f, windowSize.y / 2.f };
		sf::Vector2f SpawnLocToCenter{ center.x - spawnLoc.x, center.y - spawnLoc.y };
		Normalize(SpawnLocToCenter);

		sf::Vector2f spawnVelocity = SpawnLocToCenter * mUFOSpeed;

		weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(spawnVelocity);
		newUFO.lock()->SetActorLocation(spawnLoc);

		if (++mCurrentSpawnAmt == mSpawnAmt)
		{
			FinishStage();
		}
	}
}