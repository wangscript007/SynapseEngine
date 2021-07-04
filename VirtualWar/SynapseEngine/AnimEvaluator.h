#pragma once
#include <string>
#include <map>
#include <vector>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "glm/glm.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "Bone.h"
#include "AnimChannel.h"
class Animation;
class AnimEvaluator {
public:

	std::string Name;

	std::vector<AnimChannel*> Channels;
	bool PlayForward = true;
	float LastTime;
	float TicksPerSecond;
	float Duration;
	std::vector<std::vector<glm::mat4>> Transforms;
	std::vector<int> LastPos;
	std::vector<int> LastRot;
	std::vector<int> LastScale;

	std::vector<glm::mat4> GetTransforms(float dt);

	AnimEvaluator(aiAnimation* anim);

	int GetFrameIndex(float dt);


	void Evaluate(float dt, std::map<std::string, Bone*> bones);

	

private:

};