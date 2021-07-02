#pragma once
#include "AppState.h"
#include "GameWorld.h"
#include "GameRenderer.h"
#include "UI.h"
#include "ParticleSystem.h"
#include "EffeManager.h"
#include "PlayerFirstPerson.h"
class StateFPSTest1 :
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
    ParticleSystem* ps1;
    NodeCam* c2;
    EffeManager* fxMan;
    EffeFX* fx1;
    glm::vec3 fxPos;
    PlayerFirstPerson* p1;
};

