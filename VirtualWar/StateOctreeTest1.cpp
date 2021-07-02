#include "StateOctreeTest1.h"
#include "WorldEffects.h"
#include "ModelImport.h"
#include "UserInput.h"
void StateOctreeTest1::InitState() {

	went1 = new WorldEntity();

	auto importer = new ModelImport;


	NodeEntity* e1 = importer->ImportAI("scene\\testArena1\\testArena2.fbx", true);

	int check = 1;

	went1 = new WorldEntity();

	went1->FromNode(e1);

	//went1->SetScale(glm::vec3(0.3f, 0.3f, 0.3f));

	printf("Debugging info for world entity 1.\n");

	went1->PrintDebug();

	printf("end of debugging information.\n");

	world = new GameWorld();

	world->SetSkyBox("game\\vw\\skybox\\skyBoxAlien.fbx");
	//while(true){}


	world->AddEntity(went1);

	auto cam = world->GetCam();

	cam->SetViewport(0, 0, VirtualWarApp::rWidth, VirtualWarApp::rHeight);

	l1 = new NodeLight();

	auto l2 = new NodeLight;


	l2->SetRange(1140);
	l2->SetPosition(0, 80, 0);
	l2->SetDiffuse(Vect3(1, 1, 1));
	l1->SetRange(1440);
	l1->SetPosition(500, 230, 0);
	l1->SetDiffuse(Vect3(2, 2.0f, 2.0f));

	cam->SetPosition(0.0f, 12.0f, 12);
	cam->LookAt(0, 0, 0);
	cp = 0;
	cam->Rotate(cp, 0, 0);

	world->AddLight(l1);
	//world->AddLight(l2);

	WorldEffects::InitEffects();
	c2 = new NodeCam;

	//auto e1 = ModelImport::ImportAI()
	renderer = new GameRenderer();
	renderer->SetWorld(world);

	//oct1 = new Octree("oct/testOct3.oct");




 oct1 = new Octree(world);





	oct1->SetWorld(world);

	//oct1->Save("oct/testOct3.oct");





	act1 = new WorldActor("test\\actor\\anim1.dae");
	act1->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	printf("initialization complete.\n");
	//world->AddActor(act1);
}


void StateOctreeTest1::UpdateState() {

	//ui->Update();
	act1->UpdateAnim(0.007f);
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

	cp = cp - dy * 0.2f;
	cy = cy - dx * 0.2f;

	cam->Rotate(cp, cy, 0);

	float mspeed = 2;

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

}

void StateOctreeTest1::SetMouse(float x, float y, float z) {

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

void StateOctreeTest1::SetKey(int key, bool state) {


	if (key == GLFW_KEY_W) {



	}


}

void StateOctreeTest1::RenderState() {
	//ui->Render();
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	world->RenderShadows();


	if (UserInput::main->GetButton(1)) {
		world->Render();
	}
	else {
		oct1->RenderWorld();
	}
	//	world->RenderActors();

//	world->Render();
	//renderer->Render();



}