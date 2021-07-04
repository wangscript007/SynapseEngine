#pragma once
#include "GameWorld.h"
#include "ppBloom.h"
#include "ppSSR.h"
#include "kFrameBuffer.h"

class GameRenderer
{
public:

	GameRenderer();
	void SetWorld(GameWorld* gworld);
	void Render();

private:

	GameWorld* world;
	ppBloom* fx_bloom;
	ppSSR* fx_ssr;
	kFrameBuffer* frame_world;
	IDraw* drawer;
	
};

