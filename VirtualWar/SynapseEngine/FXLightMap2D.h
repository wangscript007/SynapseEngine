#pragma once
#include "kEffect.h"
#include "Texture2D.h"
#include "MapLight.h"

class FXLightMap2D :
    public kEffect
{
public:
    FXLightMap2D(int w, int h);
    void setPars();
    void SetLight(MapLight* l);
    void SetShadowMap(Texture2D* shadow) {
        ShadowMap = shadow;
    }
    void SetCamZ(float z) {
        camZ = z;
    }
    void setMapRot(float r) {
        mapRot = r;
    }
    void setView(glm::mat4 view) {

        vMat = view;

    }
    void SetCam(float x, float y, float z, float r) {
        CamX = x;
        CamY = y;
        camZ = z;
        mapRot = r;
    }
    void useVmat(bool b) {
        uVmat = b;
    }
    void OnlyShadow(bool b) {
        onlyShadow = b;
    }
private:
    int pw, ph;
    MapLight* light;
    Texture2D* ShadowMap;
    float camZ = 1.0f;
    float mapRot = 0.0f;
    GLuint p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
    bool gotPars = false;
    glm::mat4 vMat; // = glm::ortho((float)0, (float)pw, (float)ph, (float)0, (float)-100, (float)100);
    glm::mat4 cMat;
    float CamX, CamY;
    bool uVmat = true;
    bool onlyShadow = false;
};

