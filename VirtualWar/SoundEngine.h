#pragma once
#include "fmod.hpp"
//#include "common.h"
#include "SoundSource.h"
class SoundEngine
{
public:

	static SoundEngine* Main;

	SoundEngine();
	SoundSource* LoadSound(const char* file);

private:

	FMOD::System *Sys;


};


