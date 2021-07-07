#include "FXMeshDepth.h"

FXMeshDepth::FXMeshDepth() {

	load("data/Shader/3D/MeshDepthVert.glsl", "data/Shader/3D/MeshDepthFrag.glsl");
}

void FXMeshDepth::setPars() {

	setMat("mProj", mProj);
	setMat("mModel", mModel);
	setMat("mView", mView);

	Vect3 cp = Cam->GetPosition();
	setVec3("camP", cp.X, cp.Y, cp.Z);
	setFloat("minZ", Cam->GetMinZ());
	setFloat("maxZ", Cam->GetMaxZ());

	//SetVec3("camP", Cam.);
	//SetFloat("minZ", FXG.Cam.MinZ);
	//SetFloat("maxZ", FXG.Cam.MaxZ);

}