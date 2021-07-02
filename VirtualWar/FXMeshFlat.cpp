#include "pch.h"
#include "FXMeshFlat.h"

FXMeshFlat::FXMeshFlat() {

	load("data/Shader/3D/MeshFlatVert.glsl", "data/Shader/3D/MeshFlatFrag.glsl");
	fCol = glm::vec3(1, 1, 1);
}

void FXMeshFlat::setPars() {

	setMat("mProj", mProj);
	setMat("mModel", mModel);
	setMat("mView", mView);
	setVec3("mCol", fCol.X, fCol.Y, fCol.Z);


}