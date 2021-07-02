#pragma once
#include "NodeBase.h"
#include "FrameBufferCube.h"
#include "NodeCam.h"

class SceneGraph;
class GameWorld;

class NodeLight :
    public NodeBase
{
public:
    NodeLight();
    Vect3 GetDiffuse();
    Vect3 GetSpecular();
    float GetRange();
    float GetShininess();
    void SetDiffuse(Vect3 diff);
    void SetSpecular(Vect3 spec);
    void SetRange(float range);
    void SetShininess(float shine);
    static NodeLight* Active;
    static int ShadowMapRes;
    void DrawShadowMap(GameWorld* world, NodeCam* cam);
    void SetCam(int tar, NodeCam* cam);
    void Test(int face,NodeCam* cam,SceneGraph* graph);
    void SetPosition(Vect3 pos);
    void SetPosition(float x, float y, float z);
    void RegenShadows() {
        Reshadow = true;
    }
    FrameBufferCube* GetSB() {

        return ShadowFB;
    }
private:
    Vect3 Diffuse;
    Vect3 Specular;
    float Range;
    float Shininess;
    bool CastShadows = true;
    FrameBufferCube* ShadowFB;
    bool Reshadow = true;
};


