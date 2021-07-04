
#include "SoundSource.h"

SoundSource::SoundSource(FMOD::System*sys, FMOD::Sound* snd) {

	Sound = snd;
	Sys = sys;

}

SoundChannel* SoundSource::Play() {

	FMOD::Channel* chan;

	Sys->playSound(Sound, 0, false, &chan);

	SoundChannel* sc = new SoundChannel(Sound, chan);

	return sc;

}
