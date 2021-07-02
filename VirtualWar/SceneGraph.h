#pragma once
#include "NodeBase.h"
#include "NodeEntity.h"
#include "FXMesh3D.h"
#include "FXMeshLines.h"
#include "NodeCam.h"
#include "NodeLight.h"
#include "MeshLines.h"
#include "FXMeshFlat.h"
#include "FXMeshDepth.h"
struct RayCastInfo {

	bool Hit = false;
	Vect3 HitPoint;
	float Dist = 0;
	Vect3 HitNorm;
	NodeBase* HitNode;
	Mesh3D* HitMesh;
	int HitTri;

};

struct Ray {

	Vect3 pos;
	Vect3 dir;

};

class SceneGraph
{
public:
	
	SceneGraph();
	void AddEntity(NodeEntity* ent);
	void AddLight(NodeLight* light);
	void AddLines(MeshLines* lines);
	NodeEntity* GetEntity(int id);
	int NumEntity();
	NodeCam* GetCam();
	void SetCam(NodeCam* cam);
	void Render();
	void RenderDepth();
	void RenderDepthNode(NodeEntity* node);
	void RenderNodeFlat(NodeEntity* node);
	void RenderNode(NodeEntity* node);
	NodeBase* GetRoot() {
		return Root;
	}
	int NumLights() {
		return Lights.size();
	}

	NodeLight* GetLight(int id) {
		return Lights[id];
	}

	RayCastInfo RayCast(Vect3 p, Vect3 d, NodeBase* node);
	RayCastInfo CamPick(float x, float y, float w, float h);
	RayCastInfo CamPick(float x, float y, float w, float h, NodeBase* root);
	void Debug();
	void DebugNode(NodeBase* ent);

	void BeginPlay();
	void UpdatePlay();
	void EndPlay();
	void PausePlay();

private:
	bool Playing = false;
	FXMesh3D* FXMesh;
	FXMeshLines* FXMeshLine;
	FXMeshFlat* FXMeshFl;
	FXMeshDepth* FXDepth;

	NodeBase* Root = NULL;

	std::vector<NodeLight*> Lights;
	std::vector <MeshLines*> Lines;

	NodeCam* Cam;

};

