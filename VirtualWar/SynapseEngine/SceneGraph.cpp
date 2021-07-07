#include "SceneGraph.h"

SceneGraph::SceneGraph() {

	Root = new NodeBase();
	FXMesh = new FXMesh3D;

	FXMeshLine = new FXMeshLines;
	FXMeshFl = new FXMeshFlat;
	FXDepth = new FXMeshDepth;

	//while (true) {

	//}
	//while(true){}

	Cam = new NodeCam;
	Lights.resize(0);
	//while(true){}

}


void SceneGraph::BeginPlay() {

	Playing = true;
	Root->BeginRun();

}

void SceneGraph::UpdatePlay() {

	if (Playing) {
		Root->UpdateNode();
	}
}

void SceneGraph::AddLines(MeshLines* lines) {

	Lines.push_back(lines);

}

void SceneGraph::AddLight(NodeLight* light) {

	Lights.push_back(light);

}

void SceneGraph::AddEntity(NodeEntity* node) {

	Root->Add(node);

}

void SceneGraph::RenderNodeFlat(NodeEntity* node) {

	FXMeshFl->mProj = Cam->GetProj();
	FXMeshFl->mModel = node->GetWorld();
	FXMeshFl->mView = Cam->GetWorld();
	FXMeshFl->fCol = node->GetFlatCol();
	glDisable(GL_BLEND);
	FXMeshFl->bind();
	node->Render();
	FXMeshFl->unbind();

	for (int i = 0; i < node->NumSub(); i++) {

		RenderNodeFlat((NodeEntity*)node->GetSub(i));

	}


}

void SceneGraph::RenderNode(NodeEntity* node) {

	//node->Rotate(180, 0, 0);

	FXMesh->mProj = Cam->GetProj();
	FXMesh->mModel = node->GetWorld();
	FXMesh->mView = Cam->GetWorld();
	
	FXMesh->Cam = Cam;
	bool first = true;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);

	for (int i = 0; i < Lights.size(); i++) {
		FXMesh->Light = Lights[i];
		FXMesh->bind();
		auto sb = Lights[i]->GetSB();
		sb->GetCube()->Bind(2);
		node->Render();
		sb->GetCube()->Release(2);
		FXMesh->unbind();
		if (first) {
			glBlendFunc(GL_ONE, GL_ONE);
		}
		//glDisable(GL_DEPTH_TEST)

	}

	for (int i = 0; i < node->NumSub(); i++) {

		RenderNode((NodeEntity*)node->GetSub(i));

	}
}

void SceneGraph::Render() {

	FXMeshLine->mProj = Cam->GetProj();
	FXMeshLine->mView = Cam->GetWorld();
	FXMeshLine->LineCol = Vect3(1, 1, 1);

	glDepthFunc(GL_LEQUAL);

	for (int i = 0; i < Lines.size(); i++) {

		auto ml = Lines[i];

		FXMeshLine->LineCol = ml->GetCol();

		FXMeshLine->bind();



		ml->BindVBO();
		ml->DrawVBO();
		ml->ReleaseVBO();

		FXMeshLine->unbind();

		//glClear(GL_DEPTH_BUFFER_BIT);



	}

	for (int i = 0; i < Root->NumSub(); i++) {

		RenderNode((NodeEntity*)Root->GetSub(i));

	}

}

void SceneGraph::RenderDepthNode(NodeEntity* node) {

	FXDepth->mModel = node->GetWorld();
	FXDepth->Cam = Cam;
	bool first = true;




	FXDepth->bind();
		node->RenderNoMaterial();
	
		
		//glDisable(GL_DEPTH_TEST)

		FXDepth->unbind();

	for (int i = 0; i < node->NumSub(); i++) {

		RenderDepthNode((NodeEntity*)node->GetSub(i));

	}

}

void SceneGraph::RenderDepth() {

	FXDepth->mProj = Cam->GetProj();

	FXDepth->mView = Cam->GetWorld();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);

	for (int i = 0; i < Root->NumSub(); i++) {

		RenderDepthNode((NodeEntity*)Root->GetSub(i));

	}

}

void SceneGraph::SetCam(NodeCam* cam) {
	Cam = cam;
}

NodeCam* SceneGraph::GetCam() {

	return Cam;

}



bool GetTimeAndUV(glm::vec3 pos,glm::vec3 dir,glm::vec3 v0,glm::vec3 v1,glm::vec3 v2,glm::vec3 * hp) {

	glm::vec3 edge1 = v1 - v0;
	glm::vec3 edge2 = v2 - v0;

	glm::vec3 pvec = glm::cross(dir, edge2);

	double det = glm::dot(edge1, pvec);

	if (det > -glm::epsilon<double>() && det < glm::epsilon<double>())
	{
		return false;

	}

	double invDet = 1.0f / det;

	glm::vec3 tvec = pos - v0;

	double u = glm::dot(tvec, pvec) * invDet;

	if (u < 0 || u>1)
	{
		return false;
	}

	glm::vec3 qvec = glm::cross(tvec, edge1);

	double v = glm::dot(dir, qvec) * invDet;

	if (v < 0 || u + v>1)
	{
		return false;
	}

	double t = glm::dot(edge2, qvec) * invDet;
	
	glm::vec3 ve = glm::vec3((float)t, (float)u, (float)v);
	
	hp->x = ve.x;
	hp->y = ve.y;
	hp->z = ve.z;

	return true;
}

Vect3 GetTriCoord(float t, Vect3 pos, Vect3 dir) {

	return glm::vec3(dir.X, dir.Y, dir.Z) * t + glm::vec3(pos.X, pos.Y, pos.Z);

}

RayCastInfo RayCastNode(NodeBase* node,Vect3 p,Vect3 d) {

	RayCastInfo ri;

	ri.Hit = false;
	ri.Dist = 0;
	ri.HitMesh = NULL;
	ri.HitNode = NULL;
	ri.HitNorm = Vect3(0, 0, 0);
	ri.HitPoint = Vect3(0, 0, 0);
	ri.HitTri = 0;

	bool first = true;
	float cd = 0;
	float cu, cv;
	cu = 0;
	cv = 0;
	Mesh3D* cm = NULL;
	NodeEntity* ce = NULL;

	if (node->GetType() == NodeType::TypeEntity) {

		NodeEntity* ent = (NodeEntity*)node;
		 

		glm::mat4 ew = ent->GetWorld();


		for (int i = 0; i < ent->NumMeshes(); i++) {

			Mesh3D* mesh = ent->GetMesh(i);

		

			for (int t = 0; t < mesh->NumTris(); t++) {

				Tri tri = mesh->GetTri(t);


				Vect3 v0 = mesh->GetVertex(tri.V0).Pos;
				Vect3 v1 = mesh->GetVertex(tri.V1).Pos;
				Vect3 v2 = mesh->GetVertex(tri.V2).Pos;

				glm::vec3 g0(v0.X, v0.Y, v0.Z);
				glm::vec3 g1(v1.X, v1.Y, v1.Z);
				glm::vec3 g2(v2.X, v2.Y, v2.Z);

				g0 = ew * glm::vec4(g0, 1.0f);
				g1 = ew * glm::vec4(g1, 1.0f);
				g2 = ew * glm::vec4(g2, 1.0f);


				glm::vec3 hp(0, 0, 0);

				bool hit = GetTimeAndUV(glm::vec3(p.X, p.Y, p.Z), glm::vec3(d.X, d.Y, d.Z), g0,g1,g2,&hp);

				if (hit) {
					//printf("Hit!!!!\n");

					if (hp.x < cd || first) {

						first = false;
						cd = hp.x;
						cu = hp.y;
						cv = hp.z;
						cm = mesh;
						ce = (NodeEntity*)node;

						

					}

				}
			
			}
			

		}

	}

	if (!first) {

		ri.Hit = true;
		ri.HitNode = ce;
		ri.Dist = cd;
		ri.HitMesh = cm;
		ri.HitPoint = GetTriCoord(cd, p, d);


	}
	else {
		ri.Hit = false;
	}



	for (int i = 0; i < node->NumSub(); i++) {

		auto cn = node->GetSub(i);

		RayCastInfo inf = RayCastNode(cn,p,d);

		if (inf.Hit) {
			if (ri.Hit == false || (inf.Dist < ri.Dist)) {

				ri = inf;

			}
		}



	}

	return ri;

}

RayCastInfo SceneGraph::RayCast(Vect3 p, Vect3 d,NodeBase* node) {

	RayCastInfo res;

	res = RayCastNode(node,p,d);

	return res;

}


RayCastInfo SceneGraph::CamPick(float x, float y, float vw, float vh,NodeBase* node) {

	RayCastInfo res;

	// these positions must be in range [-1, 1] (!!!), not [0, width] and [0, height]
	float mouseX = x / (vw * 0.5f) - 1.0f;
	float mouseY = y / (vh * 0.5f) - 1.0f;

	glm::mat4 proj = Cam->GetProj();//  glm::perspective(FoV, AspectRatio, Near, Far);
	glm::mat4 view = Cam->GetWorld();// glm::lookAt(glm::vec3(0.0f), CameraDirection, CameraUpVector);

	glm::mat4 invVP = glm::inverse(proj * view);
	glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
	glm::vec4 worldPos = invVP * screenPos;

	glm::vec3 dir = glm::normalize(glm::vec3(worldPos));

	Ray r;

	r.pos = Cam->GetPosition();

	r.dir = dir;



	RayCastInfo r1 = RayCast(r.pos, r.dir,node);


	return r1;

}

RayCastInfo SceneGraph::CamPick(float x, float y,float vw,float vh) {

	return CamPick(x, y, vw, vh, Root);

}

void SceneGraph::Debug() {

	printf("Begin debug.\n");
	DebugNode(Root);
	printf("End debug.\n");

}

void SceneGraph::DebugNode(NodeBase* node) {

	printf("	Node:");
	printf(node->GetName());
	printf("\n\n");

	Vect3 p = node->GetPosition();
	Vect3 s = node->GetScale();

	printf("	Pos. X:%f Y:%f Z:%f\n",p.X,p.Y,p.Z);
	printf("	Scale. X:%f Y:%f Z:%f\n", s.X, s.Y, s.Z);

	for (int i = 0; i < node->NumSub(); i++) {
		DebugNode(node->GetSub(i));
	}

}