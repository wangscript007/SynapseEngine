#pragma once
#include <vector>
#include "WorldEntity.h"
#include "WorldDynamicEntity.h"
#include "WorldActor.h"
#include "NodeCam.h"
#include "NodeLight.h"
#include "kFrameBuffer.h"
#include "Frustum.h"
#include "Bounds.h"


class GameWorld
{
public:

	GameWorld();
	void SetCam(NodeCam* cam);
	NodeCam* GetCam();
	void AddLight(NodeLight* light);
	NodeLight* GetLight(int index);
	int NumLights() {
		return lights.size();
	}
	void AddEntity(WorldEntity* entity);
	void AddDynamicEntity(WorldDynamicEntity* entity);
	WorldEntity* GetEntity(int index);
	WorldDynamicEntity* GetDynamicEntity(int index);
	void RenderActors();
	void AddActor(WorldActor* actor);

	void SetSkyBox(const char* path);

	void RenderMaps();
	void RenderToFB();
	void Render();
	void RenderDepth();
	void RenderPosition();
	void RenderNormals();
	void RenderShadows();
	void RenderExtra();

	void UpdatePhysics();
	std::vector<kFrameBuffer*> GetMaps();
	void CheckVisible();
	void GenerateOctree();
	Bounds* GetBounds();

	int TrisInBounds(Bounds* b);

	int NumOfEntities();
	std::vector<WorldEntity*> GetEntities()
	{
		return entities;
	}

	static GameWorld* Main;

private:
	std::vector<WorldEntity*> entities;
	std::vector<WorldDynamicEntity*> dynamic_entities;
	std::vector<WorldActor*> actors;
	std::vector<WorldEntity*> vis_entities;
	std::vector<WorldDynamicEntity*> vis_dynamic_entities;
	std::vector<WorldActor*> vis_actors;
	WorldEntity* SkyBox = NULL;
	std::vector<NodeLight*> lights;
	NodeCam* Cam;
	kFrameBuffer* fbWorld;
	kFrameBuffer* fbPosition;
	kFrameBuffer* fbNormals;
	kFrameBuffer* fbDepth;
	kFrameBuffer* fbExtra;
	int visCount = -1;
};

