#include "GameWorld.h"
#include "WorldEffects.h"
#include "ModelImport.h"

GameWorld* GameWorld::Main = NULL;

GameWorld::GameWorld() {

	Cam = new NodeCam();
	lights.resize(0);
	entities.resize(0);
	dynamic_entities.resize(0);
	fbWorld = new kFrameBuffer(VirtualWarApp::rWidth, VirtualWarApp::rHeight);
	fbPosition = new kFrameBuffer(VirtualWarApp::rWidth, VirtualWarApp::rHeight);
	fbNormals = new kFrameBuffer(VirtualWarApp::rWidth, VirtualWarApp::rHeight);
	fbDepth = new kFrameBuffer(VirtualWarApp::rWidth, VirtualWarApp::rHeight);
	fbExtra = new kFrameBuffer(VirtualWarApp::rWidth, VirtualWarApp::rHeight);
	Main = this;

}

void GameWorld::SetCam(NodeCam* cam) {

	Cam = cam;

}

NodeCam* GameWorld::GetCam() {

	return Cam;

}

void GameWorld::AddLight(NodeLight* light) {

	lights.push_back(light);

}

NodeLight* GameWorld::GetLight(int index) {

	return lights[index];

}

void GameWorld::AddEntity(WorldEntity* entity) {

	entities.push_back(entity);

}

void GameWorld::AddDynamicEntity(WorldDynamicEntity* entity) {

	dynamic_entities.push_back(entity);

}

WorldEntity* GameWorld::GetEntity(int index) {

	return entities[index];

}

WorldDynamicEntity* GameWorld::GetDynamicEntity(int index) {

	return dynamic_entities[index];

}

void GameWorld::SetSkyBox(const char* path) {

	auto imp = new ModelImport;

	auto node = imp->ImportAI(path, true);

	auto we = new WorldEntity();

	we->FromNode(node);

	//AddEntity(we);
	SkyBox = we;



}


void GameWorld::RenderMaps() {

	fbPosition->bind();
	RenderPosition();
	fbPosition->unbind();
	fbNormals->bind();
	RenderNormals();
	fbNormals->unbind();
	fbDepth->bind();
	RenderDepth();
	fbDepth->unbind();
	fbExtra->bind(); 
	RenderExtra();
	fbExtra->unbind();
}

void GameWorld::RenderToFB() {

	fbWorld->bind();
	Render();
	fbWorld->unbind();

}

std::vector<kFrameBuffer*> GameWorld::GetMaps() {

	std::vector<kFrameBuffer*> maps;

	maps.resize(0);

	maps.push_back(fbWorld);
	maps.push_back(fbPosition);
	maps.push_back(fbNormals);
	maps.push_back(fbDepth);
	maps.push_back(fbExtra);

	return maps;

}

void GameWorld::AddActor(WorldActor* actor) {
	actors.push_back(actor);
}


void GameWorld::CheckVisible() {

	Frustum* fr = new Frustum(Cam->GetProj() * Cam->GetWorld());

	vis_actors.resize(0);
	vis_entities.resize(0);

	for (int i = 0; i < entities.size(); i++)
	{
		auto ent = entities[i];
		ent->GenerateBounds();

		glm::vec3 min;
		glm::vec3 max;

		min = ent->GetBoundsMin();
		max = ent->GetBoundsMax();

		//printf("min X:%f Y:%f Z:%f\n", min.x, min.y, min.z);
		//printf("max X:%f Y:%f Z:%f\n", max.x, max.y, max.z);

		if (fr->IsBoxVisible(min, max))
		{

			vis_entities.push_back(ent);
			ent->visible = true;
			//printf("Visible.\n");

		}
		else {
			ent->visible = false;
			//	printf("Not visible.\n");
		}

	}

	for (int i = 0; i < actors.size(); i++) {

		auto act = actors[i];
		act->GenerateBounds();
		
		glm::vec3 min;
		glm::vec3 max;

		min = act->GetBoundsMin();
		max = act->GetBoundsMax();

		//printf("min X:%f Y:%f Z:%f\n", min.x, min.y, min.z);
		//printf("max X:%f Y:%f Z:%f\n", max.x, max.y, max.z);

		if (fr->IsBoxVisible(min, max))
		{

			vis_actors.push_back(act);
			act->Visible = true;
			//printf("Visible.\n");

		}
		else {
			act->Visible = false;
		//	printf("Not visible.\n");
		}

		
		int a = 1;

	}

}

void GameWorld::RenderActors() {
	if (visCount < 0 || visCount>5)
	{
		visCount = 0;
		CheckVisible();
	}
	visCount++;
	bool first = true;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int i = 0; i < lights.size(); i++) {


		WorldEffects::XMesh->Light = lights[i];

		//WorldEffects::XMesh->bind();
		auto sb = lights[i]->GetSB();
		sb->GetCube()->Bind(2);
		for (int i = 0; i < vis_actors.size(); i++) {
			auto ent = vis_actors[i];
			ent->Render(Cam);
		}
		//	glClear(GL_DEPTH_BUFFER_BIT);
		sb->GetCube()->Release(2);

		if (first) {
			glBlendFunc(GL_ONE, GL_ONE);
		}
		//WorldEffects::XMesh->unbind();


	}
}

void GameWorld::Render() {

	//RenderShadows();

	if (visCount < 0 || visCount>5)
	{
		visCount = 0;
		CheckVisible();
	}
	visCount++;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDepthFunc(GL_LEQUAL);

	bool first = true;

	

	//glDepthMask(GL_TRUE);


	for (int i = 0; i < lights.size(); i++) {


		WorldEffects::XMesh->Light = lights[i];

		//WorldEffects::XMesh->bind();
		auto sb = lights[i]->GetSB();
		sb->GetCube()->Bind(2);


		for (int i = 0; i < vis_entities.size(); i++) {

			auto ent = vis_entities[i];

			ent->Render(Cam);

		}

		for (int i = 0; i < dynamic_entities.size(); i++) {

			auto ent = dynamic_entities[i];

			ent->Render(Cam);

		}

		for (int i = 0; i < vis_actors.size(); i++) {
			auto ent = vis_actors[i];
			ent->Render(Cam);
		}
	//	printf("Visible Actors:%d\n", vis_actors.size());

		//	glClear(GL_DEPTH_BUFFER_BIT);
		sb->GetCube()->Release(2);

		if (first) {
			glBlendFunc(GL_ONE, GL_ONE);
		}
		//WorldEffects::XMesh->unbind();

	
	}

	if (SkyBox != NULL) {

		glBlendFunc(GL_ONE, GL_ZERO);
		

		auto pos = Cam->GetPositionGL();
		SkyBox->SetScale(glm::vec3(7, 7, 7));
		SkyBox->SetPosition(pos);
		SkyBox->RenderFlat(Cam);
	}
}

void GameWorld::RenderNormals() {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	for (int i = 0; i < vis_entities.size(); i++) {

		auto ent = vis_entities[i];

		ent->RenderNormals(Cam);

	}

	for (int i = 0; i < dynamic_entities.size(); i++) {

		auto ent = dynamic_entities[i];

		ent->RenderNormals(Cam);

	}

	for (int i = 0; i < vis_actors.size(); i++) {
		auto ent = vis_actors[i];
		ent->RenderNormals(Cam);
	}

}

void GameWorld::RenderPosition() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	for (int i = 0; i < vis_entities.size(); i++) {

		auto ent = vis_entities[i];

		ent->RenderPosition(Cam);

	}

	for (int i = 0; i < dynamic_entities.size(); i++) {

		auto ent = dynamic_entities[i];

		ent->RenderPosition(Cam);

	}

	for (int i = 0; i < vis_actors.size(); i++) {
		auto ent = vis_actors[i];
		ent->RenderPosition(Cam);
	}

}

void GameWorld::RenderExtra() {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	for (int i = 0; i < vis_entities.size(); i++) {

		auto ent = vis_entities[i];

		ent->RenderExtra(Cam);

	}

	for (int i = 0; i < dynamic_entities.size(); i++) {

		auto ent = dynamic_entities[i];

		ent->RenderExtra(Cam);

	}

	for (int i = 0; i < vis_actors.size(); i++) {
		auto ent = vis_actors[i];
		ent->RenderExtra(Cam);
	}

}

void GameWorld::RenderShadows() {

	for (int i = 0; i < lights.size(); i++) {

		auto l = lights[i];

		l->DrawShadowMap(this, Cam);

	}

}

void GameWorld::RenderDepth()
{

	for (int i = 0; i < vis_entities.size(); i++) {

		auto ent = vis_entities[i];

		ent->RenderDepth(Cam);

	}
	for (int i = 0; i < dynamic_entities.size(); i++) {

		auto ent = dynamic_entities[i];

		ent->RenderDepth(Cam);

	}

	for (int i = 0; i < vis_actors.size(); i++) {
		auto ent = vis_actors[i];
		ent->RenderDepth(Cam);
	}
}

void GameWorld::UpdatePhysics() {

	Physics::Main->Simulate(1.0f);

	for (int i = 0; i < dynamic_entities.size(); i++) {

		auto ent = dynamic_entities[i];

		ent->UpdatePhysics();

	}

}

Bounds * GameWorld::GetBounds() {

	Bounds* r = new Bounds;

	float sx, sy, sz;
	float bx, by, bz;

	bool first = true;

	for (int i = 0; i < entities.size(); i++) {

		auto e = entities[i];

		for (int k = 0; k < e->NumMeshes(); k++) {

			auto m = e->GetMesh(k);
				
			auto verts = m->GetVertexData();

			for (int j = 0; j < verts.size(); j++)
			{

				auto v = verts[j];

				if (first) {

					sx = v.Pos.X;
					sy = v.Pos.Y;
					sz = v.Pos.Z;

					bx = v.Pos.X;
					by = v.Pos.Y;
					bz = v.Pos.Z;
					first = false;

				}
				else {

					if (v.Pos.X < sx) sx = v.Pos.X;
					if (v.Pos.Y < sy) sy = v.Pos.Y;
					if (v.Pos.Z < sz) sz = v.Pos.Z;

					if (v.Pos.X > bx) bx = v.Pos.X;
					if (v.Pos.Y > by) by = v.Pos.Y;
					if (v.Pos.Z > bz) bz = v.Pos.Z;

				}



			}

		}

	}

	r->min = glm::vec3(sx, sy, sz);
	r->max = glm::vec3(bx, by, bz);
	r->extent = glm::vec3(bx - sx, by - sy, bz - sz);

	return r;

}
	


int GameWorld::TrisInBounds(Bounds* b)
{

	int tc = 0;

	for (int i = 0; i < entities.size(); i++) {

		auto e = entities[i];

		for (int k = 0; k < e->NumMeshes(); k++) {

			auto m = e->GetMesh(k);

			auto tris = m->GetTriData();

			auto vd = m->GetVertexData();

			for (int t = 0; t < tris.size(); t++) {



				auto v0 = vd[tris[t].V0].Pos;
				auto v1 = vd[tris[t].V1].Pos;
				auto v2 = vd[tris[t].V2].Pos;
			
				if (isIn(v0, b) || isIn(v1,b) || isIn(v2, b)) {

					tc++;

				}
				

			}



			

		}

	}

	return tc;

}