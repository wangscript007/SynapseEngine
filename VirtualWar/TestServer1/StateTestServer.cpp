#include "StateTestServer.h"
#include "VirtualWarApp.h"
void StateTestServer::InitState() {

	//GameMode = new GMDeathMatch;
	//TestMap = new MapTestArena1;


	Server = new GameServer();
	ui = new UI(VirtualWarApp::rWidth, VirtualWarApp::rHeight);




}

void StateTestServer::UpdateState() {

	Server->UpdateServer();

}

void StateTestServer::RenderState() {

	std::string info = "Players:" + std::to_string(Server->GetPlayerCount());

	UI::RenderText(20, 20, info.c_str(), 1, 1, 1, 1);


	int py = 45;

	for (int i = 0; i < Server->GetPlayerCount(); i++) {

		auto inf = Server->GetPlayer(i);

		UI::RenderText(20, py, inf->Name.c_str(), 1, 1, 1, 1);
		UI::RenderText(120, py, inf->ClanName.c_str(), 1, 0, 0, 1);
		py += 30;


	}

}