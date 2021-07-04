#pragma once
#include "ParticleBase.h"
#include "Texture2D.h"
class ParticleQuad : public ParticleBase
{
public:

	//void ParticleQuad();
	ParticleBase* clone();
	void setTexture(Texture2D* tex);

	Texture2D* tex;
};

