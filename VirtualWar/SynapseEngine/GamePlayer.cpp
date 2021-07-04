#include "GamePlayer.h"

GamePlayer::GamePlayer() {

}

void GamePlayer::SetCam(NodeCam* c) {
	cam = c;
}

void GamePlayer::SetCamOffset(float x, float y, float z)
{

	CamX = x;
	CamY = y;
	CamZ = z;

}

void GamePlayer::Update() {

	glm::vec3 camPos = pyBody->GetPosition();
	
	camPos.x += CamX;
	camPos.y += CamY;
	camPos.z += CamZ;

	pyBody->GetRotation();

	cam->SetPosition(camPos.x, camPos.y, camPos.z);
	cam->SetRotation(pyBody->GetRotation());

	UpdateInput();


}

void GamePlayer::SetPosition(float x, float y, float z) {

	pyBody->SetPosition(glm::vec3(x, y, z));

}