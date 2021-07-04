#pragma once
#include <ctype.h>

#include "PxPhysicsAPI.h"
#include "Physics.h"
#include "glm/glm.hpp"
class PhysicsBody
{
public:

	virtual void InitBody() {};

	glm::vec3 GetPosition();
	glm::mat4 GetRotation();
	void SetPosition(glm::vec3 pos);
	void SetConstraint(bool x, bool y, bool z);
	void Turn(float x, float y, float z);
	void SetAngularForce(float x, float y, float z);
	void ApplyForce(float x, float y, float z);
	void ApplyLocalForce(float x, float y, float z);
	void SetForce(float x, float y, float z);
	void SetLocalForce(float x, float y, float z);
	void AddLocalForce(float x, float y, float z,float dampen);
	glm::vec3 GetForce();
	float GetRotationY();
protected:
	physx::PxRigidDynamic* body;
	physx::PxRigidStatic* sbody;
	physx::PxShape* shape;
	physx::PxMaterial* material;
	float w, h, d;
};

