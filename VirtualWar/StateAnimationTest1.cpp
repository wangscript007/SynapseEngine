#include "StateAnimationTest1.h"
#include "WorldEffects.h"
#include "ModelImport.h"
#include "UserInput.h"
void StateAnimationTest1::InitState() {

	went1 = new WorldEntity();

	auto importer = new ModelImport;


	NodeEntity* e1 = importer->ImportAI("scene\\testArena1\\testArena1.fbx", true);

	int check = 1;

	went1 = new WorldEntity();

	went1->FromNode(e1);

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


	l2->SetRange(740);
	l2->SetPosition(0, 80, 0);
	l2->SetDiffuse(Vect3(1, 2, 2));
	l1->SetRange(740);
	l1->SetPosition(500, 230, 0);
	l1->SetDiffuse(Vect3(1, 1.0f,2.0f));

	cam->SetPosition(0.0f, 192.0f, 103);
	cam->LookAt(0, 0, 0);
	cp = 0;
	cam->Rotate(cp, 0, 0);

	world->AddLight(l1);
	world->AddLight(l2);

	WorldEffects::InitEffects();

	act1 = new WorldActor("test\\actor\\anim3.dae");
	//act2 = new WorldActor("test\\actor\\anim1.dae");
//	while(true){}
//	act1 = importer->ImportActor("test\\actor\\anim1.dae",false);/
	//act1->PlayAnim(0);


	world->AddActor(act1);

	act1->PlayAnim(0);
//	world->AddActor(act2);

	act1->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
//	act1->SetPosition(glm::vec3(0, 0, 0));
//	act2->SetScale(glm::vec3(0.3f, 0.3f, 0.3f));//act1->Rotate(glm::vec3(0, 90, 0));

	//auto e1 = ModelImport::ImportAI()
	renderer = new GameRenderer();
	renderer->SetWorld(world);

	printf("initialization complete.\n");

}

int tt = 0;
void StateAnimationTest1::UpdateState() {

	if (UserInput::main->GetButton(1))
	{

	act1->UpdateAnim(0.04f);
	}
	int ct = clock();

	if (ct > tt) {
		tt = ct + 1000;
		act1->rn++;
		if (act1->rn >= act1->Meshes.size()) {

			act1->rn = 0;

		}
		printf("Mesh:%d\n", act1->rn);
	}

	//ui->Update();
	//act1->UpdateNode(0.01f);
	auto cam = world->GetCam();
	//act1->UpdateAnim(0.007f);
	//act2->UpdateAnim(0.002f);


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

	float mspeed = 2.0f;

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

void StateAnimationTest1::SetMouse(float x, float y, float z) {

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

void StateAnimationTest1::SetKey(int key, bool state) {


	if (key == GLFW_KEY_W) {



	}


}

void StateAnimationTest1::RenderState() {
	//ui->Render();
	world->RenderShadows();
	world->Render();

	//renderer->Render();




}