#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Mesh3D.h"
#include <string> 
class ActorNode
{
public:
	std::string name;
	glm::mat4 Transform;
	std::vector<ActorNode*> child;
	ActorNode* parent = NULL;
	std::vector<Mesh3D*> meshes;
};

