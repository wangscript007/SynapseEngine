#include "FXMeshLines.h"

FXMeshLines::FXMeshLines() {

	
	load("data/Shader/3D/MeshLinesVert.glsl", "data/Shader/3D/MeshLinesFrag.glsl");
	LineCol = Vect3(1, 1, 1);
}

void FXMeshLines::setPars() {

	setMat("mProj", mProj);
	//setMat("mModel", mModel);
	setMat("mView", mView);
	setVec3("lineCol", LineCol.X, LineCol.Y, LineCol.Z);

}