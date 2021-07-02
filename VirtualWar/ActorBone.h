#pragma once
#include "BoneWeight.h"
#include "glm/glm.hpp"
#include <vector>
#include <string>
class ActorBone
{
public:

	ActorBone(const char* n)
	{
		name = n;
	}
	ActorBone() {

	}
	void SetOffsetMatrix(glm::mat4 m)
	{
		OffsetMatrix = m;
	}
	glm::mat4 GetOffsetMatrix() {
		return OffsetMatrix;
	}


	std::vector<BoneWeight*> weights;
	glm::mat4 OffsetMatrix;

	glm::mat4 NodeTransform;
	glm::mat4 FinalTransform;
	std::string name;
	int numChildren;
	unsigned int* children;
	int numWeights;

};

