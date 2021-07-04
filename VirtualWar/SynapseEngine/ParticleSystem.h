#pragma once
#include <vector>
#include "ParticleBase.h"
#include "DataTypes.h"
#include "Material.h"
#include "NodeCam.h"
inline float randF(float a, float b) {

	float mr = b - a;

	float x = ((float)rand() / (float)(RAND_MAX)) * mr;

	return a + x;

}

inline glm::vec3 randV3(glm::vec3 min, glm::vec3 max) {

	glm::vec3 r;

	r.x = randF(min.x, max.x);
	r.y = randF(min.y, max.y);
	r.z = randF(min.z, max.z);

	return r;

}



class ParticleSystem
{
public:

	ParticleSystem();


	
	
	void addBase(ParticleBase* p);

	void spawn(int num);

	void Update(NodeCam* cam);
	void Render(NodeCam* cam);

private:
	std::vector<ParticleBase*> base;
	std::vector<ParticleBase*> spawned;
	glm::vec3 minPos;
	glm::vec3 maxPos;
	glm::vec3 minInertia;
	glm::vec3 maxInertia;
	float alphaMin, alphaMax;
	float lifeMin, lifeMax;
	glm::vec3 minScale;
	glm::vec3 maxScale;
	glm::vec3 minCol;
	glm::vec3 maxCol;
	GLuint VertexArray = -1;
	GLuint VertexBuffer;
	GLuint IndexBuffer=-1;
	float minSize;
	float maxSize;
};

