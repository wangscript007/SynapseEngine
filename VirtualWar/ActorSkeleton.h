#pragma once
#include <vector>
#include "ActorAnimation.h"
#include "ActorBone.h"
#include <string>
class ActorSkeleton
{
public:

	unsigned int findBoneIndex(std::string name) {

		std::string cn(name);
		for (int i = 0; i < bones.size(); i++) {


			if (bones[i]->name == cn)
			{
				return (unsigned int)i;
			}
		}
		return -1;

	}

	ActorBone* findBone(std::string name)
	{

		std::string cn(name);
		for (int i = 0; i < bones.size(); i++) {

		
			if (bones[i]->name == cn)
			{
				return bones[i];
			}
		}
		return nullptr;
	}

	std::vector<ActorAnimation*> Animations;
	glm::mat4 GlobalInverseTransform;
	std::vector<ActorBone*> bones;

};

