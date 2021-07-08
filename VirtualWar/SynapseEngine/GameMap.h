#pragma once
#include "GameWorld.h"

class GameMap
{
public:

	GameMap();
	void Init();
	virtual void LoadMap();

private:

	GameWorld* World;

};

