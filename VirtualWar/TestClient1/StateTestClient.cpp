#include "StateTestClient.h"


void StateTestClient::InitState() {

	//GameMode = new GMDeathMatch;
	//TestMap = new MapTestArena1;

	inf = new PlayerInfo("ScopeDynamo","Nomad");

	Client = new GameClient("127.0.0.1",8888,inf);
	//Client->SetPlayerInfo(inf);






}

void StateTestClient::UpdateState() {


}

void StateTestClient::RenderState() {



}