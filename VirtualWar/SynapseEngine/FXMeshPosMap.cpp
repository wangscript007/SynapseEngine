#include "FXMeshPosMap.h"

FXMeshPosMap::FXMeshPosMap() {

	load("data/Shader/3D/MeshPosVert.glsl", "data/Shader/3D/MeshPosFrag.glsl");
	//while (true) {}

}

void FXMeshPosMap::setPars() {

	setMat("mProj", mProj);
	setMat("mModel", mModel);
	setMat("mView", mView);


}