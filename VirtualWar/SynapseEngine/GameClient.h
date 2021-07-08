#pragma once
#include "SyClient.h"
#include "PlayerInfo.h"
#include <thread>
class GameClient
{
public:

	GameClient(const char* ip, int port,PlayerInfo* inf);
	void SetPlayerInfo(PlayerInfo* info);



	PlayerInfo* info = nullptr;
	SyClient* Client;

};

