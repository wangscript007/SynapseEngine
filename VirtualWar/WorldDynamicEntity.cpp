#include "WorldDynamicEntity.h"
#include "WorldEntity.h"
#include "WorldEffects.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

WorldDynamicEntity::WorldDynamicEntity() {

	meshes.resize(0);
	Reset();

}

void WorldDynamicEntity::Reset() {

	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	rotation = glm::mat4(1.0f);

}

void WorldDynamicEntity::FromNode(NodeEntity* entity) {

	position = entity->GetPositionGL();
	scale = entity->GetScaleGL();
	rotation = entity->GetTurnGL();

	for (int i = 0; i < entity->NumMeshes(); i++) {

		meshes.push_back(entity->GetMesh(i));

	}

}


void WorldDynamicEntity::Render(NodeCam* cam) {



	auto mfx = WorldEffects::XMesh;

	mfx->mProj = cam->GetProj();
	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;
	mfx->mView = cam->GetWorld();
	mfx->Cam = cam;

	//mfx->mProj = cam->GetProj();
	//mfx->mModel = rotation;;
	//mfx->mView = cam->GetWorld();
	//mfx->fCol = Vect3(1, 1, 1);


	//glDisable(GL_BLEND);
	mfx->bind();

	RenderMeshes();


	mfx->unbind();



}

void WorldDynamicEntity::RenderNormals(NodeCam* cam) {


	auto mfx = WorldEffects::XMeshNormMap;

	mfx->mProj = cam->GetProj();
	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;
	mfx->mView = cam->GetWorld();
	mfx->Cam = cam;

	mfx->bind();

	//node->RenderNoMaterial();

	RenderMeshesNoMaterial();

	mfx->unbind();



}

void WorldDynamicEntity::RenderPosition(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshPosMap;

	mfx->mProj = cam->GetProj();
	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;
	mfx->mView = cam->GetWorld();
	mfx->Cam = cam;

		mfx->bind();

		//node->RenderNoMaterial();

		RenderMeshesNoMaterial();

		mfx->unbind();




}

void WorldDynamicEntity::RenderExtra(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshPosMap;

	mfx->mProj = cam->GetProj();
	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;
	mfx->mView = cam->GetWorld();
	mfx->Cam = cam;

	mfx->bind();

	//node->RenderNoMaterial();

	RenderMeshes();

	mfx->unbind();


}

void WorldDynamicEntity::MoveStraight(float x, float y, float z) {

	position = glm::vec3(position.x + x, position.y + y, position.z + z);

}
void WorldDynamicEntity::RenderDepth(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshDepth;

	mfx->mProj = cam->GetProj();


	mfx->mView = cam->GetWorld();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;
	mfx->Cam = cam;
	bool first = true;

	mfx->bind();

	//node->RenderNoMaterial();

	RenderMeshesNoMaterial();

	mfx->unbind();


}

void WorldDynamicEntity::RenderMeshes() {



	for (int i = 0; i < meshes.size(); i++) {

		meshes[i]->BindMaterial();
		meshes[i]->BindVBO();
		meshes[i]->DrawVBO();
		meshes[i]->ReleaseVBO();
		meshes[i]->ReleaseMaterial();

	}

}

void WorldDynamicEntity::RenderMeshesNoMaterial() {

	for (int i = 0; i < meshes.size(); i++) {

		//	Meshes[i]->BindMaterial();
		meshes[i]->BindVBO();
		meshes[i]->DrawVBO();
		meshes[i]->ReleaseVBO();
		//Meshes[i]->ReleaseMaterial();

	}

}

void WorldDynamicEntity::PrintDebug() {

	printf("Meshes:%d\n", meshes.size());

	for (int i = 0; i < meshes.size(); i++) {

		Mesh3D* mesh = meshes[i];

		printf("Vertices:%d Tris:%d \n", mesh->NumVertices(), mesh->NumTris());

		Material* mat = mesh->GetMaterial();

		if (mat == NULL) {
			printf("No material\n");
		}
		else {
			printf("Has material.\n");
		}


	}


}

void WorldDynamicEntity::SetPosition(float x, float y, float z) {

	position = glm::vec3(x, y, z);

	if (pyBody == NULL) return;

	pyBody->SetPosition(position);

}

glm::vec3 WorldDynamicEntity::GetBounds() {

	glm::vec3 bb(0, 0, 0);

	float sx, sy, sz, bx, by, bz;
	sx = sy = sz = 10000;
	bx = by = bz = -10000;

	for (int i = 0; i < meshes.size(); i++) {

		auto mesh = meshes[i];

		for (int j = 0; j < mesh->NumVertices(); j++) {

			auto v = mesh->GetVertex(j);

			if (v.Pos.X < sx) sx = v.Pos.X;
			if (v.Pos.Y < sy) sy = v.Pos.Y;
			if (v.Pos.Z < sz) sz = v.Pos.Z;
			if (v.Pos.X > bx) bx = v.Pos.X;
			if (v.Pos.Y > by) by = v.Pos.Y;
			if (v.Pos.Z > bz) bz = v.Pos.Z;


		}

	}

	bb.x = bx - sx;
	bb.y = by - sy;
	bb.z = bz - sz;

	return bb;


}

void WorldDynamicEntity::SetPhysicsBox() {

	glm::vec3 bb = GetBounds();
	bb.x = bb.x + 0.1f;
	bb.y = bb.y + 0.1f;
	bb.z = bb.z + 0.1f;
	pyBody = new PBBox(bb.x,bb.y,bb.z);

}

void WorldDynamicEntity::SetPhysicsSphere() {

	glm::vec3 bb = GetBounds();
	pyBody = new PBSphere(bb.y/2.0f+0.1f);

}

void WorldDynamicEntity::SetPhysicsCapsule() {

	glm::vec3 bb = GetBounds();
	pyBody = new PBCapsule((bb.y/2.0f)-1.1f, bb.x/2.0f);

}

void WorldDynamicEntity::SetConstraint(bool x, bool y, bool z) {

	pyBody->SetConstraint(x, y, z);

}

void WorldDynamicEntity::SetPhysicsConvex() {

	pyBody = new PBConvex(this);

}

void WorldDynamicEntity::UpdatePhysics() {

	if (pyBody == NULL) return;

	position = pyBody->GetPosition();
	rotation = pyBody->GetRotation();


}

void WorldDynamicEntity::SetPosition(glm::vec3 pos) {

	position = pos;

	if (pyBody == NULL) return;

	pyBody->SetPosition(pos);


}