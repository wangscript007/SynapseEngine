#include "WorldEffects.h"

FXMesh3D * WorldEffects::XMesh = NULL;
FXMeshDepth* WorldEffects::XMeshDepth = NULL;
FXMeshFlat* WorldEffects::XMeshFlat = NULL;
FXMeshLines* WorldEffects::XMeshLines = NULL;
FXMeshPosMap* WorldEffects::XMeshPosMap = NULL;
FXMeshNormMap* WorldEffects::XMeshNormMap = NULL;
FXMeshExtra* WorldEffects::XMeshExtra = NULL;
FXMeshAnim* WorldEffects::XMeshAnim = NULL;
FXParticleSoft* WorldEffects::XParticleSoft = NULL;
void WorldEffects::InitEffects() {

	printf("initializing world effects.\n");

	XMesh = new FXMesh3D();
	XMeshDepth = new FXMeshDepth();
	XMeshFlat = new FXMeshFlat();
	XMeshLines = new FXMeshLines();
	XMeshPosMap = new FXMeshPosMap();
	XMeshNormMap = new FXMeshNormMap();
	XMeshExtra = new FXMeshExtra();
	XMeshAnim = new FXMeshAnim();
	XParticleSoft = new FXParticleSoft();
	printf("initiailized world effects.\n");


}