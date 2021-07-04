#pragma once
#include "AppState.h"
#include "UI.h"
#include "ButtonControl.h"
#include "ImageControl.h"
#include "BoolControl.h"
#include "GameWorld.h"
class StateTest2 :
    public AppState
{
public:
    void InitState();
    void UpdateState();
    void RenderState();
    void SetMouse(float x, float y, float z);
    void SetKey(int key, bool state);
private:
    UI* ui;
    bool first = true;
    float lx, ly;
    float cp = 0, cy = 0;
    GameWorld* world;
    WorldEntity* went1;
    NodeLight* l1;

};


