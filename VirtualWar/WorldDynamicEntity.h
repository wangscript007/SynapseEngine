#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Mesh3D.h"
#include "NodeEntity.h"
#include "NodeCam.h"
#include "PhysicsBody.h"
#include "PBBox.h"
#include "PBSphere.h"
#include "PBConvex.h"
#include "PBCapsule.h"
class WorldDynamicEntity
{
public:

	WorldDynamicEntity();
	void Reset();
	void FromNode(NodeEntity* entity);
	void PrintDebug();
	void Render(NodeCam* cam);
	void RenderDepth(NodeCam* cam);
	void RenderPosition(NodeCam* cam);
	void RenderNormals(NodeCam* cam);
	void RenderExtra(NodeCam* cam);
	void RenderMeshes();
	void RenderMeshesNoMaterial();
	void SetPosition(float x, float y, float z);
	void MoveStraight(float x, float y, float z);
	void SetPhysicsBox();
	void SetPhysicsSphere();
	void SetPhysicsConvex();
	void SetPhysicsCapsule();
	Mesh3D* GetMesh(int id) {
		return meshes[id];
	}
	void UpdatePhysics();
	void SetPosition(glm::vec3 pos);
	glm::vec3 GetBounds();
	void SetConstraint(bool x, bool y, bool z);
public:
	std::vector<Mesh3D*> meshes;

	glm::mat4 rotation;
	glm::vec3 position;
	glm::vec3 scale;
	PhysicsBody* pyBody = NULL;
};

