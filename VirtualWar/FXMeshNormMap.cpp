#include "FXMeshNormMap.h"
FXMeshNormMap::FXMeshNormMap() {

	load("data/Shader/3D/MeshNormVert.glsl", "data/Shader/3D/MeshNormFrag.glsl");
	//while (true) {}




}

void FXMeshNormMap::setPars() {

	setMat("mProj", mProj);
	setMat("mModel", mModel);
	setMat("mView", mView);


}