#include "NodeLight.h"
#include "NodeCam.h"
#include "SceneGraph.h"
#include "GameWorld.h"
NodeLight* NodeLight::Active = NULL;
int NodeLight::ShadowMapRes = 1024;

NodeLight::NodeLight() {

	Diffuse = Vect3(1, 1, 1);
	Specular = Vect3(1, 1, 1);
	Range = 500;
	Shininess = 0.3f;
	ShadowFB = new FrameBufferCube(ShadowMapRes, ShadowMapRes);

}

void NodeLight::SetPosition(Vect3 pos) {

	LocalPos = glm::vec3(pos.X,pos.Y,pos.Z);
	Reshadow = true;

}

void NodeLight::SetPosition(float x, float y, float z) {

	LocalPos = glm::vec3(x, y, z);
	Reshadow = true;

}

void NodeLight::DrawShadowMap(GameWorld* world,NodeCam* cam) {

	Active = this;
	
//	if (!Reshadow) return;
//	Reshadow = false;


	NodeCam* scam = new NodeCam;
	scam->SetFOV(90);
	scam->SetMinZ(cam->GetMinZ());
	scam->SetMaxZ(cam->GetMaxZ());
	scam->SetPosition(GetPosition());

	//auto vp = scam->GetPosition();
	//vp.Z = -vp.Z;
	//scam->SetPosition(vp);

	glDisable(GL_SCISSOR_TEST);
	
	NodeCam* old = world->GetCam();
	glClearColor((float)1, 1, 1, 1);

	world->SetCam(scam);
	glViewport(0, 0, ShadowMapRes, ShadowMapRes);
	scam->SetViewport(0, 0, ShadowMapRes, ShadowMapRes);

	int tar = ShadowFB->SetFace(0);
	SetCam(tar, scam);

	world->RenderDepth();

	SetCam(ShadowFB->SetFace(1), scam);
	world->RenderDepth();

	SetCam(ShadowFB->SetFace(2), scam);
	world->RenderDepth();

	SetCam(ShadowFB->SetFace(3), scam);
	world->RenderDepth();

	SetCam(ShadowFB->SetFace(4), scam);
	world->RenderDepth();

	SetCam(ShadowFB->SetFace(5), scam);
	world->RenderDepth();

	world->SetCam(old);

	ShadowFB->Release();



}

void NodeLight::Test(int f,NodeCam* cam,SceneGraph * gr) {

	NodeCam* nc = new NodeCam;

	nc->SetFOV(90);
	nc->SetViewport(0, 0, ShadowMapRes, ShadowMapRes);
	nc->SetPosition(cam->GetPosition());
	//float of = cam->GetFOV();
	//cam->SetFOV(90);

	//cam->SetViewport(0, 0, ShadowMapRes, ShadowMapRes);
	SetCam(GL_TEXTURE_CUBE_MAP_POSITIVE_X + f, nc);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	NodeCam* oc = gr->GetCam();
	gr->SetCam(nc);
	gr->RenderDepth();
	gr->SetCam(oc);


	//cam->SetFOV(of);
	//cam->SetViewport(0,0,)



}

void NodeLight::SetCam(int t, NodeCam* cam) {

	switch (t) {
	case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
		cam->LookAtZero(Vect3(1, 0, 0), Vect3(0, -1, 0));
		break;
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
		cam->LookAtZero(Vect3(-1, 0, 0), Vect3(0, -1, 0));
		break;
	case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
		cam->LookAtZero(Vect3(0, -1, 0), Vect3(0, 0, -1));
		break;
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
		cam->LookAtZero(Vect3(0, 1, 0), Vect3(0, 0, 1));
		break;
	case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
		cam->LookAtZero(Vect3(0, 0, 1), Vect3(0, -1, 0));
		break;
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
		cam->LookAtZero(Vect3(0, 0, -1), Vect3(0, -1, 0));
		break;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Vect3 NodeLight::GetDiffuse() {

	return Diffuse;

}

Vect3 NodeLight::GetSpecular() {

	return Specular;

}

float NodeLight::GetRange()
{
	return Range;
}

float NodeLight::GetShininess() {

	return Shininess;

}

void NodeLight::SetDiffuse(Vect3 diff) {

	Diffuse = diff;

}

void NodeLight::SetSpecular(Vect3 spec) {

	Specular = spec;

}

void NodeLight::SetRange(float range) {

	Range = range;

}

void NodeLight::SetShininess(float shine) {

	Shininess = shine;

}