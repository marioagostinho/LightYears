#include <framework/World.h>

#include "enemy/VanguardStage.h"
#include "enemy/TwinBlade.h"
#include "enemy/Vanguard.h"

namespace ly
{
	VanguardStage::VanguardStage(World* world)
		: GameStage(world),
		mSpawnInterval(1.f),
		mSwitchInterval(4.f),
		mSpawnDistanceToEdge(100.f),
		mLeftSpawnLoc{0.f, 0.f},
		mRightSpawnLoc{0.f, 0.f},
		mSpawnLoc{0.f, 0.f},
		mRowsToSpawn(2),
		mRowSpawnCount(0),
		mVarguardsPerRow(5),
		mCurrentRowVanguardCount(0)
	{
	}

	void VanguardStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();
		mLeftSpawnLoc = sf::Vector2f{ mSpawnDistanceToEdge, -100.f };
		mRightSpawnLoc = sf::Vector2f{ windowSize.x - mSpawnDistanceToEdge, -100.f };

		SwitchRow();
	}

	void VanguardStage::SwitchRow()
	{
		if (mRowSpawnCount == mRowsToSpawn)
		{
			FinishStage();
			return;
		}

		mSpawnLoc = (mSpawnLoc == mLeftSpawnLoc) ? mRightSpawnLoc : mLeftSpawnLoc;
		mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);

		++mRowSpawnCount;
	}

	void VanguardStage::SpawnVanguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(mSpawnLoc);
		++mCurrentRowVanguardCount;

		if (mCurrentRowVanguardCount == mVarguardsPerRow)
		{
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
			mCurrentRowVanguardCount = 0;
		}
	}

	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
		TimerManager::Get().ClearTimer(mSwitchTimerHandle);
	}
}