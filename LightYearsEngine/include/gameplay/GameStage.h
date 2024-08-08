#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World *world);

		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		void FinishStage();

		Delegate<> onStageFinished;

		const World *GetWorld() const { return mWorld; }
		World *GetWorld() { return mWorld; }

		bool IsStageFinished() const { return mStageFinished; }

	private:
		virtual void StageFinished();

		World *mWorld;
		bool mStageFinished;
	};
}