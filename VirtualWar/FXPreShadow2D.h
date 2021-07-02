#pragma once
#include "kEffect.h"
#include "MapLight.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Texture2D.h"
class FXPreShadow2D :
    public kEffect
{
public:
    FXPreShadow2D(int w,int h);
    void setPars();
    void SetCam(float x, float y, float z, float r) {
        CamX = x;
        CamY = y;

        mapRot = r;
    }
private:

    int sW, sH;
    GLuint p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14;
    bool gotPars = false;
    float mapRot = 0;
    glm::mat4 vMat;
    float CamX, CamY;

};

