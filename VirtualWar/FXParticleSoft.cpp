#include "FXParticleSoft.h"


FXParticleSoft::FXParticleSoft() {

	load("data/Shader/PS/ParticleVert.glsl", "data/Shader/PS/ParticleFrag.glsl");

	//while(true){}
	//}

}

void FXParticleSoft::setPars() {

	setMat("mProj", mProj);
	setMat("mModel", mModel);
	setMat("mView", mView);

	auto vp = Cam->GetPosition();

	setInt("tCol", 0);


	Vect3 viewVec = Cam->GetViewVec();


	auto vpos = Cam->GetPosition();


}