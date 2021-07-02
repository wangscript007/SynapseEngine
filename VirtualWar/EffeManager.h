#pragma once
#include <stdio.h>
#include <string>
#include "NodeCam.h"
#include <Effekseer.h>

struct EffeFX {

	Effekseer::EffectRef ref;

};

struct EffeHandle {

	Effekseer::Handle handle = 0;

};

class EffeManager
{
public:

	EffeManager();
	void SetCam(NodeCam* cam);
	EffeFX* LoadFX(const char16_t* path);
	EffeHandle* Play(EffeFX* fx,glm::vec3 pos);
	void Stop(EffeHandle* fx);
	void update();

	void render();

private:
	
	::Effekseer::ManagerRef manager;
};

