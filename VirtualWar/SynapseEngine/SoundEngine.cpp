#include <stdio.h>
#include "SoundEngine.h"
#include <fmod_errors.h>

SoundEngine* SoundEngine::Main = nullptr;

SoundEngine::SoundEngine() {

	FMOD_RESULT result = FMOD::System_Create(&Sys);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	//	exit(-1);
	}


	result = Sys->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		//exit(-1);
	}

	Main = this;

}

SoundSource* SoundEngine::LoadSound(const char* path) {

	FMOD::Sound* snd;

	Sys->createSound(path, FMOD_DEFAULT, 0, &snd);
	snd->setMode(FMOD_LOOP_OFF);

	return new SoundSource(Sys, snd);


}