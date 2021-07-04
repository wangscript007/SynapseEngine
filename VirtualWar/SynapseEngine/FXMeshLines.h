#pragma once
#include "kEffect.h"
#include "DataTypes.h"
class FXMeshLines :
    public kEffect
{
public:
    FXMeshLines();
    void setPars();

    glm::mat4 mProj;
    glm::mat4 mView;
    Vect3 LineCol;
    //NodeLight* Light;
    //NodeCam* Cam;


};

