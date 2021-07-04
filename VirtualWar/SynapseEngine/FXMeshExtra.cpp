#include "FXMeshExtra.h"

FXMeshExtra::FXMeshExtra() {

	load("data/Shader/3D/MeshExtraVert.glsl", "data/Shader/3D/MeshExtraFrag.glsl");
	//while (true) {}




	//}

}

void FXMeshExtra::setPars() {

	setMat("mProj", mProj);
	setMat("mModel", mModel);
	setMat("mView", mView);


	setInt("tCol", 0);
	setInt("tNorm", 1);
	setInt("tSpec", 3);
	setInt("tShadow", 2);






}