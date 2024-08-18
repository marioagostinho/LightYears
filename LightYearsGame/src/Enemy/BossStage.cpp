#include <framework/World.h>

#include "enemy/Boss.h"
#include "enemy/BossStage.h"

namespace ly
{
	BossStage::BossStage(World* world)
		: GameStage(world)
	{
	}

	void BossStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();

		weak<Boss> boss = GetWorld()->SpawnActor<Boss>();
		boss.lock()->SetActorLocation({ windowSize.x / 2.f, 200.f });
		boss.lock()->onActorDestroyed.BindAction(GetWeakRef(), &BossStage::BossDestroyed);
	}
	void BossStage::BossDestroyed(Actor* actor)
	{
		FinishStage();
	}
}