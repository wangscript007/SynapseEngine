#pragma once
#include "SoundChannel.h"
#include <fmod.hpp>
class SoundSource
{
public:

	SoundSource(FMOD::System * sys,FMOD::Sound* snd);
	SoundChannel* Play();



private:

	FMOD::Sound *Sound;
	FMOD::System* Sys;
};

