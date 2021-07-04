#pragma once
//#include "GameWorld.h"
#include "WorldChunk.h"
#include <fstream>>
#include <ostream>
class GameWorld;


class Octree
{
public:
	Octree(const char* path);
	Octree(GameWorld* w);
	void Optimize();
	void ProcessWorld();
	void RenderShadows();
	void RenderWorld();
	void Save(const char* path);
	void SetWorld(GameWorld* w) {
		world = w;
		worldChunk->SetWorld(w);
	}


private:
	GameWorld* world;
	int TriLimit = 6000;
	WorldChunk* worldChunk;
};

