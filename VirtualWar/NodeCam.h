#pragma once
#include "NodeBase.h"
class NodeCam : public NodeBase
{
public:

	NodeCam();
	void SetViewport(int x, int y, int w, int h);
	glm::mat4 GetProj() {

		return mProj;
	}
	
	float GetMinZ() {
		return minZ;
	}

	float GetMaxZ() {
		return maxZ;
	}
	float GetFOV() {
		return FOV;
	}
	void SetFOV(float fov) {
		FOV = fov;
	}
	void SetMinZ(float minz) {
		minZ = minz;
	}
	void SetMaxZ(int maxz) {
		maxZ = maxz;
	}
	void LookAtZero(Vect3 l, Vect3 up)
	{
		LocalTurn = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(l.X, l.Y, l.Z), glm::vec3(up.X, up.Y, up.Z));
		//LocalTurn = glm::inverse(LocalTurn);
	}

	Vect3 GetViewVec() {
		glm::vec3 v = glm::vec3(0, 0, 1);

		glm::vec3 r = LocalTurn * glm::vec4(v, 1.0f);
	

		return Vect3(r.x, r.y, r.z);
	}

	glm::mat4 GetWorld();

private:
	glm::mat4 mProj;
	float minZ;
	float maxZ;
	float FOV = 45;
};

