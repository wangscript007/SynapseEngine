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
#include "AnimEvaluator.h"
class WorldActor;


class Animator
{
public:

	Animator();
	void InitAssImp(const aiScene* aiRoot, WorldActor* root);

	Bone* _skeleton;
	std::map<std::string, Bone*> _bonesByName;
	std::map<std::string, int> _bonesByIndex;
	std::map<std::string, int> _animationNameToId;
	std::vector<Bone*> _bones;
	std::vector<AnimEvaluator*> Animations;

	int GetBoneIndex(std::string name);
	void SetAnimationIndex(int index);

	int _i = 0;

	void Calculate(float dt);

	void UpdateTransforms(Bone* node);

	void ExtractAnimations(const aiScene* scene);

	void CalculateBoneToWorldTransform(Bone* child);

	Bone* CreateBoneTree(aiNode* node, Bone* parent);

	int CurrentAnimationIndex = 0;
	bool HasSkeleton() {
		if (_bones.size() > 0) return true;
		return false;
	}

	std::string AnimationName() {

		return Animations[CurrentAnimationIndex]->Name;

	}

	float AnimationSpeed() {

		return Animations[CurrentAnimationIndex]->TicksPerSecond;

	}

	float Duration() {

		return Animations[CurrentAnimationIndex]->Duration / Animations[CurrentAnimationIndex]->TicksPerSecond;

	}

	std::vector<glm::mat4> GetTransforms(float dt) {

		return Animations[CurrentAnimationIndex]->GetTransforms(dt);

	}



};

