#pragma once
#include "kEffect.h"
#include "NodeLight.h"
#include "NodeCam.h"
class FXParticleSoft :
    public kEffect
{
public:
    FXParticleSoft();
    void setPars();

    glm::mat4 mProj;
    glm::mat4 mModel;
    glm::mat4 mView;
    NodeLight* Light;
    NodeCam* Cam;
};

