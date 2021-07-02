#include "ParticleQuad.h"

ParticleBase* ParticleQuad::clone() {

	ParticleQuad* q = new ParticleQuad;
	q->setAlpha(alpha);
	q->setAlphaMod(alphaMod);
	q->setColor(color);
	q->setColorMod(colorMod);
	q->setInertia(inertia);
	q->setLife(life);
	q->setLifeMod(lifeMod);
	q->SetPos(pos);
	q->setScale(scale);
	q->setScaleMod(scaleMod);
	q->setTexture(tex);
	return q;


}

void ParticleQuad::setTexture(Texture2D* t) {

	tex = t;

}