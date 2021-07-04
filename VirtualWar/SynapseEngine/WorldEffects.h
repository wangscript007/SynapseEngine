#pragma once
#include "FXMesh3D.h"
#include "FXMeshDepth.h"
#include "FXMeshFlat.h"
#include "FXMeshLines.h"
#include "FXMeshPosMap.h"
#include "FXMeshNormMap.h"
#include "FXMeshExtra.h"
#include "FXMeshAnim.h"
#include "FXParticleSoft.h"

class WorldEffects
{
public:
	
	static void InitEffects();
	static FXMesh3D* XMesh;
	static FXMeshDepth* XMeshDepth;
	static FXMeshFlat* XMeshFlat;
	static FXMeshLines* XMeshLines;
	static FXMeshPosMap* XMeshPosMap;
	static FXMeshNormMap* XMeshNormMap;
	static FXMeshExtra* XMeshExtra;
	static FXMeshAnim* XMeshAnim;
	static FXParticleSoft* XParticleSoft;

private:

};

