#pragma once
#include "Mesh3D.h"
#include <vector>
#include "NodeBase.h"

class NodeEntity : public NodeBase
{
public:

	NodeEntity();
	void AddMesh(Mesh3D* mesh);
	Mesh3D* GetMesh(int id);
	int NumMeshes();
	void Render();
	void RenderNoMaterial();


private:

	std::vector<Mesh3D*> Meshes;

};


