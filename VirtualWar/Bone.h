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

struct Bone {

	std::string Name;
	glm::mat4 Offset;
	glm::mat4 LocalTransform;
	glm::mat4 GlobalTransform;
	glm::mat4 OriginalLocalTransform;
	Bone* Parent;
	std::vector<Bone*> Children;

};
