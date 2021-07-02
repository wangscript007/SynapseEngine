#include "WorldEntity.h"
#include "WorldEffects.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
WorldEntity::WorldEntity() {

	meshes.resize(0);
	Reset();

}

void WorldEntity::Reset() {

	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	rotation = glm::mat4(1.0f);

}

void WorldEntity::FromNode(NodeEntity* entity) {

	position = entity->GetPositionGL();
	scale = entity->GetScaleGL();
	rotation = entity->GetTurnGL();

	for (int i = 0; i < entity->NumMeshes(); i++) {

		meshes.push_back(entity->GetMesh(i));

	}

}

void WorldEntity::GenerateBounds() {




		if (boundsGenerated) return;
		boundsGenerated = true;

		bool first = true;

		float sx, sy, sz;
		float bx, by, bz;


		for (int m = 0; m < meshes.size(); m++)
		{

			auto Mesh = meshes[m];

			for (int i = 0; i < Mesh->NumVertices(); i++) {

				auto v = Mesh->GetVertex(i);

				auto vp = glm::vec3(v.Pos.X, v.Pos.Y, v.Pos.Z);

				glm::mat4 sm = glm::scale(scale);

				vp = sm * glm::vec4(vp, 1.0);

				if (first) {

					sx = vp.x;
					sy = vp.y;
					sz = vp.z;

					bx = vp.x;
					by = vp.y;
					bz = vp.z;

					first = false;

				}
				else {

					if (vp.x < sx) sx = vp.x;
					if (vp.y < sy) sy = vp.y;
					if (vp.z < sz) sz = vp.z;

					if (vp.x > bx) bx = vp.x;
					if (vp.y > by) by = vp.y;
					if (vp.z > bz) bz = vp.z;

				}

			}

		}

			Bounds.x = bx - sx;
			Bounds.y = by - sy;
			Bounds.z = bz - sz;

			printf("Bounds. X:%f Y:%f Z:%f\n", Bounds.x, Bounds.y, Bounds.z);

		


}

glm::vec3 WorldEntity::GetBoundsMax() {

	float px, py, pz;

	px = position.x;
	py = position.y;
	pz = position.z;

	glm::vec3 p1;

	p1.x = px + Bounds.x;// / 2.0f;
	p1.y = py + Bounds.y;// / 2.0f;
	p1.z = pz + Bounds.z;// / 2.0f;

	return p1;

}

glm::vec3 WorldEntity::GetBoundsMin() {

	float px, py, pz;

	px = position.x;
	py = position.y;
	pz = position.z;

	glm::vec3 p1;

	p1.x = px - Bounds.x;// / 2.0f;
	p1.y = py - Bounds.y;// / 2.0f;
	p1.z = pz - Bounds.z;// / 2.0f;

	return p1;
	//bb[0] = p1;


	//bb[0] = //glm::vec2(px - Bounds.x / 2, py - Bounds.y/2, pz - Bounds.z/2);
	//bb[1] =///glm::vec2(px + B
		//ounds.x / 2, py + Bounds.y / 2, pz + Bounds.z);


}

void WorldEntity::Render(NodeCam* cam) {



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

void WorldEntity::RenderFlat(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshFlat;

	mfx->mProj = cam->GetProj();
	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;


	mfx->mView = cam->GetWorld();
//	mfx->Cam = cam;

	mfx->bind();

	RenderMeshes();


	mfx->unbind();
}

void WorldEntity::RenderDepth(NodeCam* cam) {

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

void WorldEntity::RenderNormals(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshNormMap;

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

void WorldEntity::RenderPosition(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshPosMap;

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

void WorldEntity::RenderExtra(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshExtra;

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

	RenderMeshes();

	mfx->unbind();


}

void WorldEntity::RenderMeshes() {

	

	for (int i = 0; i < meshes.size(); i++) {

		meshes[i]->BindMaterial();
		meshes[i]->BindVBO();
		meshes[i]->DrawVBO();
		meshes[i]->ReleaseVBO();
		meshes[i]->ReleaseMaterial();

	}

}

void WorldEntity::RenderMeshesNoMaterial() {

	for (int i = 0; i < meshes.size(); i++) {

		//	Meshes[i]->BindMaterial();
		meshes[i]->BindVBO();
		meshes[i]->DrawVBO();
		meshes[i]->ReleaseVBO();
		//Meshes[i]->ReleaseMaterial();

	}

}

void WorldEntity::SetPosition(glm::vec3 pos) {

	position = pos;

}

void WorldEntity::SetPosition(float x, float y, float z) {

	position = glm::vec3(x, y, z);

}

void WorldEntity::PrintDebug() {

	printf("Meshes:%d\n", meshes.size());

	for (int i = 0; i < meshes.size(); i++) {

		Mesh3D* mesh = meshes[i];

		printf("Vertices:%d Tris:%d \n", mesh->NumVertices(),mesh->NumTris());

		Material* mat = mesh->GetMaterial();

		if (mat == NULL) {
			printf("No material\n");
		}
		else {
			printf("Has material.\n");
		}


	}


}

int WorldEntity::NumVertices() {

	int vc = 0;

	for (int i = 0; i < meshes.size(); i++) {

		vc += meshes[i]->NumVertices();

	}

	return vc;
}

int WorldEntity::NumTris() {

	int tc = 0;

	for (int i = 0; i < meshes.size(); i++) {

		tc += meshes[i]->NumTris();

	}

	return tc;

}

int WorldEntity::NumMeshes() {

	return meshes.size();

}

Mesh3D* WorldEntity::GetMesh(int index) {

	return meshes[index];

}

void WorldEntity::SetPhysicsTris() {

	for (int i = 0; i < meshes.size(); i++) {

		pyBody = new PBTriangles(this, i);

	}

	//pyBody = new PBTriangles(this);

}