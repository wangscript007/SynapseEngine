#pragma once
#include <vector>
#include "Mesh3D.h"
#include "Bounds.h"
#include "NodeCam.h"
#include <map>
class GameWorld;

struct TriLink {

	Mesh3D* mesh;
	int TriIndex;
	Mesh3D* owner;

};

class WorldChunk
{
public:

	WorldChunk();
	void Assume(GameWorld* w, Bounds* b, int triLimit);

	void Split();
	void Gather();
	void Render(NodeCam* cam,bool checkBounds);
	void RenderDepth(NodeCam* cam);
	void RenderMeshes();
	void RenderMeshesNoMaterial();
	void GetRenderList(NodeCam* cam,bool checkBounds);
	static int renderCount;
	static std::vector<WorldChunk*> rlist;
	std::vector<Mesh3D*> GetMeshes();
	static std::vector<TriLink> AllLinks;
	static std::map<Mesh3D*, std::vector<TriLink>> triMap;
	void Write(FILE* file);
	void Read(FILE* file);
	void SetWorld(GameWorld* w) {


		world = w;
		for (int i = 0; i < sub.size(); i++) {
			sub[i]->SetWorld(w);
		}

	}
	std::vector<Mesh3D*> GetAllMeshes();
private:

	std::vector<Mesh3D*> meshes;
	std::vector<TriLink> Tris;
	std::vector<WorldChunk*> sub;
	Bounds* bounds;
	glm::vec3 centre;
	GameWorld* world;
	int triLimit;
	bool Container = false;

};

