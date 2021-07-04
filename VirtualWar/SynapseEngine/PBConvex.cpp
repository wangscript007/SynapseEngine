#include "PBConvex.h"
#include "WorldDynamicEntity.h"


PBConvex::PBConvex(WorldDynamicEntity* ent)
{
	entity = ent;
	InitBody();

}

void PBConvex::InitBody() {

	physx::PxCookingParams params = Physics::GetCooking()->getParams();

	// Use the new (default) PxConvexMeshCookingType::eQUICKHULL
	params.convexMeshCookingType = physx::PxConvexMeshCookingType::eQUICKHULL;/// convexMeshCookingType;


	// If the gaussMapLimit is chosen higher than the number of output vertices, no gauss map is added to the convex mesh data (here 256).
	// If the gaussMapLimit is chosen lower than the number of output vertices, a gauss map is added to the convex mesh data (here 16).
	params.gaussMapLimit = 64;
	Physics::GetCooking()->setParams(params);


	auto mesh = entity->GetMesh(0);

	if (mesh->GetTri(0).V0 == 0 && mesh->GetTri(0).V1 == 0) {

		return;
	}

	//	return;

	int vc = mesh->NumVertices();
//	int tc = mesh->NumTris();

	physx::PxVec3* vertData = new physx::PxVec3[vc];



	int vid = 0;

	//for (int i = 0; i < entity->NumMeshes(); i++) {




	for (int k = 0; k < mesh->NumVertices(); k++) {

		auto vert = mesh->GetVertex(k);
		vertData[vid] = physx::PxVec3(vert.Pos.X, vert.Pos.Y, vert.Pos.Z);
		vid++;

	}



	physx::PxConvexMeshDesc desc;

	// We provide points only, therefore the PxConvexFlag::eCOMPUTE_CONVEX flag must be specified
	desc.points.data = vertData;
	desc.points.count = vc;
	desc.points.stride = sizeof(physx::PxVec3);
	desc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX;

	physx::PxU32 meshSize = 0;
	physx::PxConvexMesh* convex = NULL;

	convex = Physics::GetCooking()->createConvexMesh(desc, Physics::GetSDK()->getPhysicsInsertionCallback());

	physx::PxMaterial* mat;

	mat = Physics::GetSDK()->createMaterial(0.5f, 0.5f, 0.6f);

	auto shape = Physics::GetSDK()->createShape(physx::PxConvexMeshGeometry(convex), *mat);;

	physx::PxTransform   tm(0, 0, 0);

	body = Physics::GetSDK()->createRigidDynamic(tm);

	body->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, true);

	body->attachShape(*shape);


	Physics::GetScene()->addActor(*body);

}