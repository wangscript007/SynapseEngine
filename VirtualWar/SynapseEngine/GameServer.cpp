#include "GameServer.h"

GameServer::GameServer() {

	InitNetworking();

	printf("Starting host server.\n");
	Host = new SyHost(8888);
	printf("Started host server.\n");

}

void GameServer::UpdateServer() {
    
    

    int ec = Host->EventCount();


    int bb = 5;
    NetMsg* m1;

    for (int i = 0; i < ec; i++) {

        NetEvent evt = Host->GetEvent(i);

        switch (evt.Type) {
        case NetEventType::NewClientConnected:

            bb = 5;

            m1 = new NetMsg("requestInfo", 0,MsgSendType::Reliable, 256);
            Host->Send(m1, evt.Peer);
            printf("Send name request to peer.\n");


            break;

        case NetEventType::NewMessage:

            auto msg = evt.Msg;
            if (msg->GetChannel() == "clientInfo")
            {

                std::string name, clan;

                name = msg->PullString();
                clan = msg->PullString();

                printf("Client info received. Name:");
                printf(name.c_str());
                printf(" Clan:");
                printf(clan.c_str());
                printf("\n");
                PlayerCount++;

                PlayerInfo* inf = new PlayerInfo(name, clan);
                Players.push_back(inf);

            }


         

        }

    }

    if (ec == Host->EventCount()) {
        Host->ClearEvents();
    }

}