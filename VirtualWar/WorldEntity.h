#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Mesh3D.h"
#include "NodeEntity.h"
#include "NodeCam.h"
#include "PBTriangles.h"
class WorldEntity
{
public:
	
	WorldEntity();
	void Reset();
	void FromNode(NodeEntity* entity);
	void PrintDebug();
	void Render(NodeCam* cam);
	void RenderFlat(NodeCam* cam);
	void RenderDepth(NodeCam* cam);
	void RenderPosition(NodeCam* cam);
	void RenderNormals(NodeCam* cam);
	void RenderExtra(NodeCam* cam);
	void RenderMeshes();
	void RenderMeshesNoMaterial();
	int NumVertices();
	int NumTris();
	int NumMeshes();
	Mesh3D* GetMesh(int index);
	void SetPhysicsTris();
	void SetPosition(glm::vec3 pos);
	void SetPosition(float x, float y, float z);
	void SetScale(glm::vec3 sca) {
		scale = sca;
	}
	void GenerateBounds();
	glm::vec3 GetBoundsMin();
	glm::vec3 GetBoundsMax();
	bool visible = false;
private:
	glm::vec3 Bounds;
	bool boundsGenerated = false;
	std::vector<Mesh3D*> meshes;

	glm::mat4 rotation;
	glm::vec3 position;
	glm::vec3 scale;

	PBTriangles* pyBody;

};

