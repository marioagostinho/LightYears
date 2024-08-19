#pragma once

#include <framework/Core.h>

#include "player/Player.h"

namespace ly
{
	class PlayerManager
	{
	public:
		static PlayerManager& Get();

		Player& CreateNewPlayer();

		Player* GetPlayer(int playerIndex = 0);
		const Player* GetPlayer(int playerIndex = 0) const;

		void Reset();
	protected:
		PlayerManager();

	private:
		List<Player> mPlayers;
		static unique<PlayerManager> playerManager;
	};
}