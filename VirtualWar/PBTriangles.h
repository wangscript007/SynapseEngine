#pragma once
#include "PhysicsBody.h"

class WorldEntity;

class PBTriangles :
    public PhysicsBody
{
public:
    //PBTriangles(WorldEntity* entity);
    PBTriangles();
    PBTriangles(WorldEntity* entity,int index);
private:
    physx::PxTriangleMesh* triMesh = NULL;
};


