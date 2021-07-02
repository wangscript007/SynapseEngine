#pragma once
#include "kEffect.h"
#include "NodeCam.h"

class FXMeshDepth :
    public kEffect
{
public:

    FXMeshDepth();
    void setPars();


    glm::mat4 mProj;
    glm::mat4 mModel;
    glm::mat4 mView;
    //NodeLight* Light;
    NodeCam* Cam;
};

