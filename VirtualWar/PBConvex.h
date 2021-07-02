#pragma once
#include "PhysicsBody.h"

class WorldDynamicEntity;

class PBConvex :
    public PhysicsBody
{
public:

    PBConvex(WorldDynamicEntity* entity);
    void InitBody();

private:

    WorldDynamicEntity* entity;

};

