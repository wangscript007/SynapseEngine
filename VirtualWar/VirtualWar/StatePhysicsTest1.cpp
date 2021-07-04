#include "StatePhysicsTest1.h"

#include "GameIncludes.h"
#include "EngineGlobal.h"
#include "UITheme.h"
#include "UITheme_Neon.h"
#include "ModelImport.h"
#include "WorldEffects.h"
#include "UserInput.h"

void StatePhysicsTest1::InitState() {

	printf("Starting test editor state.\n");
	ui = new UI(EngineGlobals::rWidth, EngineGlobals::rHeight);

	went1 = new WorldEntity();

	auto importer = new ModelImport;


	NodeEntity* b1 = importer->ImportAI("test\\dynamic\\capsule1.fbx", true);
	NodeEntity* b2 = importer->ImportAI("test\\dynamic\\sphere1.fbx", true);
	NodeEntity* b3 = importer->ImportAI("test\\dynamic\\hull1.fbx", true);

	NodeEntity* e1 = importer->ImportAI("test\\world\\worldEntity2.fbx", true);

	int check = 1;

	went1 = new WorldEntity();

	went1->FromNode(e1);

	WorldDynamicEntity* d1 = new WorldDynamicEntity();
	WorldDynamicEntity* d2 = new WorldDynamicEntity();
	WorldDynamicEntity* d3 = new WorldDynamicEntity();

	d1->FromNode(b1);
	d2->FromNode(b2);
	d3->FromNode(b3);

	d1->SetPhysicsCapsule();
	d2->SetPhysicsSphere();
	d3->SetPhysicsConvex();

	d1->SetConstraint(true, false, true);

	d1->SetPosition(4.0f,15,0);
	d2->SetPosition(2, 12, 0);
	d3->SetPosition(1, 8, 0);

	went1->SetPhysicsTris();

	printf("Debugging info for world entity 1.\n");

	//went1->PrintDebug();
	d1->PrintDebug();

	printf("end of debugging information.\n");

	world = new GameWorld();

	world->AddEntity(went1);
	world->AddDynamicEntity(d1);
	world->AddDynamicEntity(d2);
	world->AddDynamicEntity(d3);
	

	auto cam = world->GetCam();

	cam->SetViewport(0, 0, VirtualWarApp::rWidth, VirtualWarApp::rHeight);

	l1 = new NodeLight();

	auto l2 = new NodeLight;


	l2->SetRange(2800);
	l2->SetPosition(130, 80, 130);
	l2->SetDiffuse(Vect3(1, 1, 1));
	l1->SetRange(2800);
	l1->SetPosition(500, 230, 0);
	l1->SetDiffuse(Vect3(1, 1.0f, 1.0f));

	cam->SetPosition(0.0f, 10,20);
	cam->LookAt(0, 0, 0);
	cp = 0;
	cam->Rotate(cp, 0, 0);

	world->AddLight(l1);
	world->AddLight(l2);

	WorldEffects::InitEffects();

	//auto e1 = ModelImport::ImportAI()


	printf("initialization complete.\n");

}

void StatePhysicsTest1::UpdateState() {

	ui->Update();

	auto cam = world->GetCam();

	float mx, my;

	mx = UserInput::main->MouseX();
	my = UserInput::main->MouseY();

	if (first) {
		first = false;
		lx = mx;
		ly = my;
	}

	float dx = mx - lx;
	float dy = my - ly;

	lx = mx;
	ly = my;

	cp = cp - dy * 0.6f;
	cy = cy - dx * 0.6f;

	cam->Rotate(cp, cy, 0);

	float mspeed = 0.2f;

	if (UserInput::main->KeyDown(GLFW_KEY_W))
	{

		cam->Move(0, 0, -mspeed);

	}
	if (UserInput::main->KeyDown(GLFW_KEY_S)) {

		cam->Move(0, 0, mspeed);

	}

	if (UserInput::main->KeyDown(GLFW_KEY_A)) {

		cam->Move(-mspeed, 0, 0);

	}

	if (UserInput::main->KeyDown(GLFW_KEY_D))
	{
		cam->Move(mspeed, 0, 0);
	}

	if (UserInput::main->GetButton(0)) {


		l1->SetPosition(cam->GetPosition());

	}

	if (UserInput::main->GetButton(1))
	{

		world->UpdatePhysics();
	}
}

void StatePhysicsTest1::SetMouse(float x, float y, float z) {

	if (first) {
		first = false;
		lx = x;
		ly = y;
	}

	float mx = x - lx;
	float my = y - ly;

	lx = x;
	ly = y;

	auto cam = world->GetCam();

	cp = cp - my * 0.2f;
	cy = cy - mx * 0.2f;

	cam->Rotate(cp, cy, 0);

}

void StatePhysicsTest1::SetKey(int key, bool state) {


	if (key == GLFW_KEY_W) {



	}


}

void StatePhysicsTest1::RenderState() {

	world->RenderShadows();

	world->Render();

	ui->Render();


}