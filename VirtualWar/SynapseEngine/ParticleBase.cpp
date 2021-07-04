#include "ParticleBase.h"

void ParticleBase::SetPos(glm::vec3 p)
{

	pos = p;

}

void ParticleBase::setScale(glm::vec3 s) {

	scale = s;

}

void ParticleBase::setColor(glm::vec3 c) {

	color = c;

}


void ParticleBase::setAlpha(float a)
{
	alpha = a;

}

void ParticleBase::setLife(float l) {

	life = l;

};


void ParticleBase::setAlphaMod(float am) {

	alphaMod = am;

}

void ParticleBase::setLifeMod(float lm)
{

	lifeMod = lm;

}


void ParticleBase::setInertia(glm::vec3 i)
{

	inertia = i;

}

void ParticleBase::setScaleMod(glm::vec3 sm) {

	scaleMod = sm;

}
void ParticleBase::setColorMod(glm::vec3 cm)
{

	colorMod = cm;

}