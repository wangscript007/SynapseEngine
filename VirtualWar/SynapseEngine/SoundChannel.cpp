
#include "SoundChannel.h"

SoundChannel::SoundChannel(FMOD::Sound* snd, FMOD::Channel* chan) {
	Sound = snd;
	Channel = chan;
}

void SoundChannel::Pause() {

	Channel->setPaused(true);

}

void SoundChannel::Stop() {

	Channel->stop();

}

void SoundChannel::Free() {

	Channel->stop();
	//delete Channel;

}

bool SoundChannel::IsPlaying() {

	bool res = false;

	 Channel->isPlaying(&res);

	 return res;
}