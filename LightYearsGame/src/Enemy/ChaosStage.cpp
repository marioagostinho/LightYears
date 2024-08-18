#include <framework/World.h>
#include <framework/MathUtility.h>

#include "enemy/Vanguard.h"
#include "enemy/TwinBlade.h"
#include "enemy/Hexagon.h"
#include "enemy/UFO.h"
#include "enemy/ChaosStage.h"

namespace ly
{
	ChaosStage::ChaosStage(World* world)
		: GameStage(world),
		mSpawnInterval(4.f),
		mMinSpawnInterval(0.8f),
		mSpawnIntervalDecrement(0.5f),
		mSpawnIntervalDecrementInterval(5.f),
		mStageDuration(60.f)
	{
	}

	void ChaosStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
		mDifficultTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::IncreaseDifficulty, mSpawnIntervalDecrementInterval, true);
		TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, mStageDuration);
	}

	void ChaosStage::SpawnVanguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade, mSpawnInterval);
	}

	void ChaosStage::SpawnTwinBlade()
	{
		weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetActorLocation(GetRandomSpawnLocationTop());

		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexagon, mSpawnInterval);
	}

	void ChaosStage::SpawnHexagon()
	{
		weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(GetRandomSpawnLocationTop());

		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO, mSpawnInterval);
	}

	void ChaosStage::SpawnUFO()
	{
		sf::Vector2f spawnLoc = GetRandomSpawnLocationSide();

		auto windowSize = GetWorld()->GetWindowSize();
		sf::Vector2f center = sf::Vector2f{ windowSize.x / 2.f, windowSize.y / 2.f };
		
		sf::Vector2f dirToCenter = center - spawnLoc;
		Normalize(dirToCenter);

		weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(dirToCenter * 200.f);
		newUFO.lock()->SetActorLocation(spawnLoc);

		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
	}

	void ChaosStage::IncreaseDifficulty()
	{
		mSpawnInterval -= mSpawnIntervalDecrement;

		if (mSpawnInterval <= mMinSpawnInterval) 
		{
			mSpawnInterval = mMinSpawnInterval;
			TimerManager::Get().ClearTimer(mDifficultTimerHandle);
		}
	}

	void ChaosStage::StageDurationReached()
	{
		FinishStage();
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
	{
		auto windowSize = GetWorld()->GetWindowSize();
		float spawnX = RandomRange(100.f, windowSize.x - 100.f);
		float spawnY = -100.f;

		return { spawnX, spawnY };
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationSide() const
	{
		auto windowSize = GetWorld()->GetWindowSize();

		float spawnLeft = RandomRange(-1, 1);
		float spawnLocY = RandomRange(0, windowSize.y);
		float spawnLocX = 0;

		spawnLocX = (spawnLeft < 0) ? windowSize.x + 100.f : -100;

		return sf::Vector2f{ spawnLocX, spawnLocY };
	}

	void ChaosStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimer);
		TimerManager::Get().ClearTimer(mDifficultTimerHandle);
	}
}