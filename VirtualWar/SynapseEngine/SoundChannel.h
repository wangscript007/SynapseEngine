#pragma once
#include <fmod.hpp>
class SoundChannel
{
public:
	SoundChannel(FMOD::Sound* snd, FMOD::Channel* chan);
	void Pause();
	void Stop();
	bool IsPlaying();
	void Free();
private:

	FMOD::Channel *Channel;
	FMOD::Sound* Sound;

};

