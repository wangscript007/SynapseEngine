#pragma once
#define GM_SERVER
#include "AppState.h"
#include "GameServer.h"
#include "UI.h"
#include "ButtonControl.h"
//#include "Control"


class StateTestServer :
    public AppState
{
public:
        
    void InitState();
    void UpdateState();
    void RenderState();

private:

    //GameMode* GameMode;
    //GameMap* TestMap;
    GameServer* Server;
    UI* ui;

};

