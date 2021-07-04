#include "pch.h"
#include "NodeCam.h"
#include <glm/ext.hpp>
#include "TMaths.h"
NodeCam::NodeCam() {

	minZ = 0.1f;
	maxZ = 1000.0f;

}

void NodeCam::SetViewport(int x, int y, int w, int h) {

	float nv = TMaths::DegToRad(FOV);
	mProj = glm::perspective<float>(nv, (float)w / (float)h, minZ, maxZ);
	//mProj = glm::perspectiveFov(FOV, (float)w, (float)h, minZ, maxZ);


}


glm::mat4 NodeCam::GetWorld() {

	glm::mat4 world = NodeBase::GetWorld();

	glm::mat ret = glm::inverse(world);

	return ret;

}