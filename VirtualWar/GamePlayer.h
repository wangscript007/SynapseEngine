#pragma once
#include "PhysicsBody.h"
#include "PBBox.h"
#include "PBSphere.h"
#include "PBConvex.h"
#include "PBCapsule.h"
#include "NodeCam.h"

class GamePlayer
{
public:
	
	GamePlayer();
	void SetCam(NodeCam* c);
//	void Set
	void SetCamOffset(float x, float y, float z);
	void UpdateCam();
	void Update();
	void SetPosition(float x, float y, float z);
	virtual void UpdateInput() {};

protected:

	float CamX, CamY, CamZ;

	PhysicsBody* pyBody = NULL;
	NodeCam* cam;
};

