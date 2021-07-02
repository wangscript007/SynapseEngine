#pragma once
#include "AnimationChannel.h"
#include <string>
class ActorAnimation
{
public:
	std::string name;
	double duration;
	double ticksPerSecond;
	std::vector<AnimationChannel*> channels;

	AnimationChannel* FindChannel(std::string name) {

		for (int i = 0; i < channels.size(); i++) {

			if (channels[i]->name == name)
			{
				return channels[i];
			}

		}
		return nullptr;

	}

};

