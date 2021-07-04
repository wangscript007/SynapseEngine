#pragma once
#include "kEffect.h"
#include "MapLight.h"
#include "Texture2D.h"

class FXSoftParticle2D :
    public kEffect
{
public:
    FXSoftParticle2D(int w, int h);
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
private:
    int pw, ph;
    MapLight* light;
    Texture2D* ShadowMap;
    float camZ = 1.0f;
    float mapRot = 0.0f;
    GLuint p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14;
    bool gotPars = false;
};

