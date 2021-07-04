#pragma once
#include "glm/glm.hpp"
class ParticleBase
{
public:
	void SetPos(glm::vec3 p );
	void setScale(glm::vec3 s);
	void setColor(glm::vec3 c);
	void setAlpha(float alpha);
	void setLife(float life);
	void setAlphaMod(float am);
	void setLifeMod(float lm);
	void setInertia(glm::vec3 i);
	void setScaleMod(glm::vec3 sm);
	void setColorMod(glm::vec3 cm);
	virtual ParticleBase* clone() { return nullptr; };
	void Render();
	glm::vec3 GetPos()
	{
		return pos;
	}

	bool operator<(ParticleBase& that) {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
	float cameradistance = 0.0;
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 color;
	float size = 0.1f;
	float sizeMod = 0.1f;
	float alpha = 1.0f;
	float life = 1.0f;
	//
	float alphaMod = 1.0f;
	float lifeMod = 1.0f;
	glm::vec3 inertia;
	glm::vec3 scaleMod;
	glm::vec3 colorMod;


};

