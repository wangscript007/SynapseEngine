#pragma once
#include "AppState.h"
#include "GameWorld.h"
#include "GameRenderer.h"
#include "UI.h"
#include "Octree.h"
class StateOctreeTest1 :
    public AppState
{
public:

    void InitState();
    void UpdateState();
    void RenderState();
    void SetMouse(float x, float y, float z);
    void SetKey(int key, bool state);

private:
    GameWorld* world;
    GameRenderer* renderer;
    UI* ui;
    bool first = true;
    float lx, ly;
    float cp = 0, cy = 0;
    WorldActor* act1;
    WorldEntity* went1;
    NodeLight* l1;
    Octree* oct1;
    NodeCam* c2;
};

