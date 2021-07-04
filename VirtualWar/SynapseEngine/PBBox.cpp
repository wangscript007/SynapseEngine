#include "PBBox.h"


PBBox::PBBox(float bw,float bh,float bd) {

	w = bw;
	h = bh;
	d = bd;
	InitBody();

}

void PBBox::InitBody() {

	physx::PxTransform   tm(0, 0, 0);

	material = Physics::GetSDK()->createMaterial(0.5f, 0.5f, 0.6f);


	shape = Physics::GetSDK()->createShape(physx::PxBoxGeometry(w / 2.0f, h / 2.0f, d / 2.0f), *material);
	body = Physics::GetSDK()->createRigidDynamic(tm);
	body->attachShape(*shape);
	physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
	body->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, true);
	Physics::GetScene()->addActor(*body);


	//body = physx::PxCreateDynamic(Physics::GetSDK(), tm, geo, mat, 10.0f);

}
