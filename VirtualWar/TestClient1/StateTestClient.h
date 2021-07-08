#pragma once
#include "AppState.h"
#include "GameClient.h"
class StateTestClient :
    public AppState
{
public:

    void InitState();
    void UpdateState();
    void RenderState();

private:

    //GameMode* GameMode;
    //GameMap* TestMap;
    GameClient* Client;
    PlayerInfo* inf;
};

