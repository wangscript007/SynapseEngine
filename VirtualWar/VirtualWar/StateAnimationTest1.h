#pragma once
#include "AppState.h"
#include "GameWorld.h"
#include "WorldEntity.h"
#include "WorldDynamicEntity.h"
#include "GameRenderer.h"
#include "UI.h"
#include "WorldActor.h"
class StateAnimationTest1 :
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
    GameRenderer* renderer;
    WorldDynamicEntity* box1;
    WorldDynamicEntity* sphere1;
    WorldActor* act1;
    WorldActor* act2;
};

