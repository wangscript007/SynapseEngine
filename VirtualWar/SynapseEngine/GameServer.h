#pragma once
#include "SyHost.h"
#include "PlayerInfo.h"
#include <vector>

class GameServer
{
public:

	GameServer();
	void UpdateServer();
	int GetPlayerCount() {
		return PlayerCount;
	}
	PlayerInfo* GetPlayer(int id) {
		return Players[id];
	}

private:
	SyHost* Host;
	int PlayerCount = 0;
	std::vector<PlayerInfo*> Players;
};


