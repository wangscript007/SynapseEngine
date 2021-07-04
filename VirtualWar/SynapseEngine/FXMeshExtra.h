#pragma once
#include "kEffect.h"
#include "NodeLight.h"
#include "NodeCam.h"
class FXMeshExtra :
    public kEffect
{
public:
    FXMeshExtra();
    void setPars();

    glm::mat4 mProj;
    glm::mat4 mModel;
    glm::mat4 mView;
    NodeLight* Light;
    NodeCam* Cam;
};

