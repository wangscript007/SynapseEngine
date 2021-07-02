#include "WorldChunk.h"
#include "GameWorld.h"
#include <map>
#include "WorldEffects.h"
#include "NodeCam.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

inline glm::vec3 rv3(FILE* f) {

	glm::vec3 r;
	float v1;

	fread((void*)&v1, 4, 1, f);
	r.x = v1;
	fread((void*)&v1, 4, 1, f);
	r.y = v1;
	fread((void*)&v1, 4, 1, f);
	r.z = v1;

	return r;

}

inline bool rbool(FILE* f) {


	char r;

	fread((void*)&r, 1, 1, f);
	if (r == 0) {
		return false;
	}
	return true;

}

inline int rint(FILE* f) {

	int r;
	fread((void*)&r, 4, 1, f);

	return r;
}

inline void wv3(glm::vec3 v, FILE* f) {

	fwrite((const void*)&v.x, 4, 1, f);
	fwrite((const void*)&v.y, 4, 1, f);
	fwrite((const void*)&v.z, 4, 1, f);

}

inline void wint(int v, FILE* f) {

	fwrite((const void*)&v, 4, 1, f);

}

inline void wbool(bool v, FILE* f) {

	if (v) {
		char v1 = 1;
		fwrite((const void*)&v1, 1, 1, f);
	}
	else {
		char v2 = 0;
		fwrite((const void*)&v2, 1, 1, f);
	}
}


inline void wstring(const char* b, FILE* f) {

	int len = 0;

	for (int i = 0; i < 2555; i++) {

		if (b[i] == "\0"[0])
		{
			break;
		}
		len++;
	}

	wint(len, f);
	fwrite((const void*)b, len, 1, f);

}

const char* rstring(FILE* f) {

	int len = rint(f);
	char* buf = (char*)malloc(len + 1);
	fread((void*)buf, len, 1, f);
	buf[len] = "\0"[0];
	return buf;
}

WorldChunk::WorldChunk()
{

	meshes.resize(0);
	sub.resize(0);

}

void WorldChunk::Assume(GameWorld* w, Bounds* b, int tl) {





	int tc = 0;
	int tt = w->TrisInBounds(b);
	triLimit = tl;

	bounds = b;

	world = w;

	centre = glm::vec3(b->max.x - b->min.x, b->max.y - b->min.y, b->max.z - b->min.z);

	if (tt > triLimit) {

		Container = true;
		Split();

	}
	else if(tt>0) {

		Container = false;
		Gather();

	}

	int a = 11;


}



std::vector<TriLink> WorldChunk::AllLinks;
std::map<Mesh3D*, std::vector<TriLink>> WorldChunk::triMap;

void WorldChunk::Gather() {

	auto el = world->GetEntities();

	std::vector<TriLink> tris;

	tris.resize(0);

	for (int i = 0; i < el.size(); i++) {

		auto e = el[i];

		for (int j = 0; j < e->NumMeshes(); j++) {

			auto m = e->GetMesh(j);

	

			auto tl = m->GetTriData();
			auto vl = m->GetVertexData();

			for (int t = 0; t < m->NumTris(); t++) {

				Tri tr = tl[t];

				auto v0 = vl[tr.V0].Pos;
				auto v1 = vl[tr.V1].Pos;
				auto v2 = vl[tr.V2].Pos;

				if (isIn(v0, bounds) || isIn(v1, bounds) || isIn(v2, bounds))
				{
					bool skip = false;
					std::vector<TriLink> tris1 = triMap[m];
					
					for (int i = 0; i < tris1.size(); i++) {

						if (tris1[i].TriIndex == t)
						{
							skip = true;
							break;
						}

					}

					/*
					bool skip = false;
					for (int l = 0; l < AllLinks.size(); l++) {

						auto clink = AllLinks[l];
						int ctt = clink.TriIndex;

						if (ctt == t && clink.owner == m) {
							skip = true;
							break;
						}
					}
					*/
					if (skip) continue;
					TriLink link;
					link.TriIndex = t;
					link.owner = m;
					tris.push_back(link);
					triMap[m].push_back(link);
					//AllLinks.push_back(link);
					

				}

			}

		}

	}

	std::map<Mesh3D*, std::vector<TriLink>> am;

	for (int i = 0; i < tris.size(); i++) {

		auto om = tris[i].owner;

		if (am.contains(om))
		{
			am[om].push_back(tris[i]);


			//tl.push_back(tris[i]);
			//am[om] = tl;
			//printf("Pushed: C:%d\n", am[om].size());

		}
		else {

			am[om].push_back(tris[i]);
			//printf("Pushed back: C:%d\n", am[om].size());

		}


	}
	

	// show content:
	for (std::map<Mesh3D*, std::vector<TriLink>>::iterator it = am.begin(); it != am.end(); ++it)
	{
		Mesh3D* nm = new Mesh3D;
		nm->SetVertexData(it->first->GetVertexData());
		nm->SetMaterial(it->first->GetMaterial());
		nm->SetData(it->first);
		meshes.push_back(nm);


		auto otris = it->first->GetTriData();


		for (int t = 0; t < it->second.size(); t++) {

			auto at = otris[it->second[t].TriIndex];



			nm->AddTri(at);
			
		}

	//	std::cout << it->first << " => " << it->second.size() << '\n';
	}

	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->CreateVBO();
	}
	int a = 11;

}

void WorldChunk::Split() {

	printf("Splitting.\n");

	int a = 25;

	WorldChunk* topFLeft, *topFRight, *topBLeft, *topBRight;
	WorldChunk* botFLeft, *botFRight, *botBLeft, *botBRight;

	botBLeft = new WorldChunk;

	glm::vec3 m, mx;


	m.x = bounds->min.x;
	m.y = bounds->min.y;
	m.z = bounds->min.z;

	mx.x = bounds->min.x + bounds->extent.x / 2.0f;
	mx.y = bounds->min.y + bounds->extent.y / 2.0f;
	mx.z = bounds->min.z + bounds->extent.z / 2.0f;

	Bounds * b = new Bounds(m, mx);

	botBLeft->Assume(world,b, triLimit);
	
	botBRight = new WorldChunk;

	m.x = bounds->min.x + bounds->extent.x / 2.0f;
	m.y = bounds->min.y;
	m.z = bounds->min.z;

	mx.x = m.x+bounds->extent.x/2.0f;
	mx.y = m.y + bounds->extent.y / 2.0f;
	mx.z = bounds->min.z + bounds->extent.z / 2.0f;

	b = new Bounds(m, mx);

	botBRight->Assume(world, b, triLimit);
	
	botFLeft = new WorldChunk;

	m.x = bounds->min.x;
	m.y = bounds->min.y;
	m.z = bounds->min.z + bounds->extent.z/2.0;

	mx.x = bounds->min.x + bounds->extent.x / 2.0;
	mx.y = bounds->min.y + bounds->extent.y / 2.0;
	mx.z = bounds->max.z;

	b = new Bounds(m, mx);

	botFLeft->Assume(world, b, triLimit);

	botFRight = new WorldChunk;

	m.x = bounds->min.x + bounds->extent.x / 2.0f;
	m.y = bounds->min.y;
	m.z = bounds->min.z + bounds->extent.z / 2.0;

	mx.x = bounds->max.x;
	mx.y = bounds->min.y + bounds->extent.y / 2.0;
	mx.z = bounds->max.z;

	b = new Bounds(m, mx);
	botFRight->Assume(world, b, triLimit);
	
	sub.push_back(botBLeft);
	sub.push_back(botBRight);
	sub.push_back(botFLeft);
	sub.push_back(botFRight);

	//-----------------

	topBLeft = new WorldChunk;

	//glm::vec3 m, mx;


	m.x = bounds->min.x;
	m.y = bounds->min.y + bounds->extent.y / 2.0f;;
	m.z = bounds->min.z;

	mx.x = bounds->min.x + bounds->extent.x / 2.0f;
	mx.y = bounds->max.y;// +bounds->extent.y / 2.0f;
	mx.z = bounds->min.z + bounds->extent.z / 2.0f;

	b = new Bounds(m, mx);

	topBLeft->Assume(world, b, triLimit);

	topBRight = new WorldChunk;

	m.x = bounds->min.x + bounds->extent.x / 2.0f;
	m.y = bounds->min.y + bounds->extent.y / 2.0f;
	m.z = bounds->min.z;

	mx.x = m.x + bounds->extent.x / 2.0f;
	mx.y = bounds->max.y;
	mx.z = bounds->min.z + bounds->extent.z / 2.0f;

	b = new Bounds(m, mx);

	topBRight->Assume(world, b, triLimit);

	topFLeft = new WorldChunk;

	m.x = bounds->min.x;
	m.y = bounds->min.y + bounds->extent.y / 2.0f;
	m.z = bounds->min.z + bounds->extent.z / 2.0;

	mx.x = bounds->min.x + bounds->extent.x / 2.0;
	mx.y = bounds->max.y;
	mx.z = bounds->max.z;

	b = new Bounds(m, mx);

	topFLeft->Assume(world, b, triLimit);


	topFRight = new WorldChunk;

	m.x = bounds->min.x + bounds->extent.x / 2.0f;
	m.y = bounds->min.y + bounds->extent.y / 2.0f;
	m.z = bounds->min.z + bounds->extent.z / 2.0f;

	mx.x = bounds->max.x;
	mx.y = bounds->max.y;
	mx.z = bounds->max.z;

	b = new Bounds(m, mx);
	topFRight->Assume(world, b, triLimit);


	sub.push_back(botBLeft);
	sub.push_back(botBRight);
	sub.push_back(botFLeft);
	sub.push_back(botFRight);
	sub.push_back(topBLeft);
	sub.push_back(topBRight);
	sub.push_back(topFLeft);
	sub.push_back(topFRight);

}

std::vector<WorldChunk*> WorldChunk::rlist;

void WorldChunk::GetRenderList(NodeCam* cam,bool checkBounds) {

	auto c = world->GetCam();

	
		Frustum* fs = new Frustum(c->GetProj() * c->GetWorld());

		if (!fs->IsBoxVisible(bounds->min, bounds->max))
		{
			//printf("Not Rendering chunk.\n");
			return;
		}

	//if(C)
	//if(Container)
	if (Container) {
		for (int s = 0; s < sub.size(); s++) {
			sub[s]->GetRenderList(cam,true);
		}
		return;
	}

	rlist.push_back(this);

	
}

void WorldChunk::Render(NodeCam* cam,bool checkBounds) {


	//printf("Rendering chunk.\n");


	WorldChunk::renderCount++;

	auto mfx = WorldEffects::XMesh;

	mfx->mProj = cam->GetProj();
	//glm::mat4 sm = glm::scale(scale);


	//glm::vec3 np(position.x, position.y, position.z);

	//glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	//fm = fm * rotation * sm;


	mfx->mModel = glm::mat4(1.0);


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
	WorldChunk::renderCount++;


}

int WorldChunk::renderCount = 0;

void WorldChunk::RenderDepth(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshDepth;

	mfx->mProj = cam->GetProj();


	mfx->mView = cam->GetWorld();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);

	//glm::mat4 sm = glm::scale(scale);


//	glm::vec3 np(position.x, position.y, position.z);

	//glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	//fm = fm * rotation * sm;

	mfx->mModel = glm::mat4(1.0f);
	mfx->Cam = cam;
	bool first = true;

	mfx->bind();

	//node->RenderNoMaterial();

	RenderMeshesNoMaterial();

	mfx->unbind();


}



void WorldChunk::RenderMeshes() {



	for (int i = 0; i < meshes.size(); i++) {

		meshes[i]->BindMaterial();
		meshes[i]->BindVBO();
		meshes[i]->DrawVBO();
		meshes[i]->ReleaseVBO();
		meshes[i]->ReleaseMaterial();

	}

}

void WorldChunk::RenderMeshesNoMaterial() {

	for (int i = 0; i < meshes.size(); i++) {

		//	Meshes[i]->BindMaterial();
		meshes[i]->BindVBO();
		meshes[i]->DrawVBO();
		meshes[i]->ReleaseVBO();
		//Meshes[i]->ReleaseMaterial();

	}

}

void WorldChunk::Read(FILE* file) {

	glm::vec3 min, max, ext, cen;

	min = rv3(file);// file->ReadVec3();
	max = rv3(file);// file->ReadVec3();


	bounds = new Bounds(min, max);

	centre = rv3(file);

	if (rbool(file)) {

		Container = true;

		int ss = rint(file);

		for (int i = 0; i < ss; i++) {

			WorldChunk* sc = new WorldChunk;

			sc->Read(file);

			sub.push_back(sc);


		}

	}
	else {

		Container = false;

		int mc = rint(file);// file->ReadInt();

		for (int i = 0; i < mc; i++) {
		
			Mesh3D* m = new Mesh3D();

			meshes.push_back(m);
			
			int vc = rint(file);// file->ReadInt();

			for (int j = 0; j < vc; j++) {

				glm::vec3 pos, norm, tan, bi, col, uv;

				pos = rv3(file);// file->ReadVec3();
				norm = rv3(file);// file->ReadVec3();
				bi = rv3(file);// file->ReadVec3();
				tan = rv3(file);// file->ReadVec3();
				uv = rv3(file);// file->ReadVec3();
				//col = rv3(file);// file->ReadVec3();

				Vertex v;

				v.Pos = Vect3(pos);
				v.Col = Vect4(1,1,1,1);
				v.Norm = Vect3(norm);
				v.BiNorm = Vect3(bi);
				v.Tan = Vect3(tan);
				v.UV = Vect3(uv);

				m->AddVertex(v);


			}

			int tc = rint(file);// file->ReadInt();

			for (int j = 0; j < tc; j++) {

				Tri t;

				t.V0 = rint(file);// file->ReadInt();
				t.V1 = rint(file);// file->ReadInt();
				t.V2 = rint(file);// file->ReadInt();

				m->AddTri(t);

			}

			Material* mat = new Material();

			mat->SetColorTex(new Texture2D(rstring(file), false));
			mat->SetNormalTex(new Texture2D(rstring(file), false));
			mat->SetSpecularTex(new Texture2D(rstring(file), false));


			m->SetMaterial(mat);

			m->CreateVBO();

		
		}


	}

}




void WorldChunk::Write(FILE* file) {


	wv3(bounds->min, file);
	wv3(bounds->max, file);
	wv3(centre, file);



	wbool(Container, file);
	//file->WriteBool(Container);


	if (Container) {

		//file->WriteInt(sub.size());
		wint(sub.size(), file);


		for (int i = 0; i < sub.size(); i++) {
			
			sub[i]->Write(file);

		}

	}
	else {

		//file->WriteInt(meshes.size());
		wint(meshes.size(), file);

		for (int i = 0; i < meshes.size(); i++) {

			auto m = meshes[i];

			auto verts = m->GetVertexData();

			//file->WriteInt(verts.size());
			wint(verts.size(),file);

			for (int j = 0; j < verts.size(); j++) {

				auto v = verts[j];

				wv3(glm::vec3(v.Pos.X, v.Pos.Y, v.Pos.Z),file);
				wv3(glm::vec3(v.Norm.X, v.Norm.Y, v.Norm.Z),file);
				wv3(glm::vec3(v.BiNorm.X, v.BiNorm.Y, v.BiNorm.Z),file);
				wv3(glm::vec3(v.Tan.X, v.Tan.Y, v.Tan.Z),file);
				wv3(glm::vec3(v.UV.X, v.UV.Y, v.UV.Z),file);
				//file->WriteVec3(glm::vec3(v.Col.X, v.Col.Y, v.Col.Z));



			}

			auto tris = m->GetTriData();

			//file->WriteInt(tris.size());
			wint(tris.size(), file);

			for (int j = 0; j < tris.size(); j++) {

				auto t = tris[j];

				wint(t.V0, file);
				wint(t.V1, file);
				wint(t.V2, file);

				//file->WriteInt(t.V0);
				//file->WriteInt(t.V1);
				//file->WriteInt(t.V2);


			}

			auto mat = m->GetMaterial();

			wstring(mat->GetColorTex()->GetPath(),file);
			wstring(mat->GetNormalTex()->GetPath(), file);
			wstring(mat->GetSpecularTex()->GetPath(), file);

		//	file->WriteString(mat->GetColorTex()->GetPath());
		//	file->WriteString(mat->GetNormalTex()->GetPath());
		//	file->WriteString(mat->GetSpecularTex()->GetPath());


		}

	}

	//file->WriteFloat(bounds->m


}