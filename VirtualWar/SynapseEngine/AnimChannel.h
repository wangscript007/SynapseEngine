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
class VectorKey {
public:
	double Time = 0.0;
	glm::vec3 Value;

};

class QuatKey {
public:
	double Time = 0.0;
	glm::quat Value;

};

class AnimChannel {
public:

	std::string Name;
	std::vector<VectorKey*>PositionKeys;
	std::vector<QuatKey*>RotationKeys;
	std::vector<VectorKey*>ScalingKeys;


private:

};
