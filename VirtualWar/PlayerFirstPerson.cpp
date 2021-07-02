#include "PlayerFirstPerson.h"
#include "UserInput.h"
#include <GLFW\glfw3.h>
PlayerFirstPerson::PlayerFirstPerson(float h, float r)
{

	pyBody = new PBCapsule(h, r);
	pyBody->SetConstraint(true, false, true);

}
bool first = true;
float lx, ly;
float moveX=0, moveZ=0;

void PlayerFirstPerson::UpdateInput() {

	float mx = UserInput::main->MouseX();
	float my = UserInput::main->MouseY();

	bool forward = UserInput::main->KeyDown(GLFW_KEY_W);
	bool sLeft = UserInput::main->KeyDown(GLFW_KEY_A);
	bool sRight = UserInput::main->KeyDown(GLFW_KEY_D);
	bool back = UserInput::main->KeyDown(GLFW_KEY_S);

	

	if (first) {
		lx = mx;
		ly = my;
		first = false;
	}

	float xd, yd;

	xd = mx - lx;
	yd = my - ly;
	if (xd > 0) {
		printf("Turning\n");
	}

	pyBody->SetAngularForce(0, -xd*0.2f, 0);
	lookY += yd * 0.2f;



	moveX = 0;
	moveZ = 0;

	if (forward)
	{

		moveZ = -5;

		//pyBody->SetLocalForce(0, 0, -100);

	}
	if (back) {

		moveZ = 4;

	}
	if (sLeft) {

		moveX = -4;

	}

	if (sRight) {
		moveX = 4;
	}

	pyBody->AddLocalForce(moveX, 0, moveZ,0.95f);

	cam->AddRotate(-lookY,0, 0);

	lx = mx;
	ly = my;

}