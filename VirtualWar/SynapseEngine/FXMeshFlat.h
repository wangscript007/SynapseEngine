#pragma once
#include "kEffect.h"
#include "DataTypes.h"
class FXMeshFlat :
    public kEffect
{
public:

    FXMeshFlat();
    void setPars();



    glm::mat4 mProj;
    glm::mat4 mModel;
    glm::mat4 mView;
    Vect3 fCol;

};

