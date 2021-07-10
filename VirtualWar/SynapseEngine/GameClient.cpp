#include "GameClient.h"

void Client_Thr(GameClient* cli)
{

    while (true) {



        cli->Client->lock();
        int ec = cli->Client->EventCount();
        if (ec > 0) {
            printf("Events:%d\n", ec);
        }

        for (int i = 0; i < ec; i++) {

            auto evt = cli->Client->GetEvent(i);

            if (evt.Type == NetEventType::NewMessage) {

                int aa = 5;
                //  printf("Processing message.\n");
                if (evt.Msg->GetChannel() == "requestInfo")
                {

                    NetMsg* name = new NetMsg("clientInfo", 0,MsgSendType::Reliable, 256);
                    name->PushString(cli->info->Name);
                    name->PushString(cli->info->ClanName);
                    
                    //name->PushString(clientName);

                    if (cli->info == nullptr) {

                        printf("Innfo not found.\n");
                        continue;

                    }

                    printf("Send playerinfo to server.\n");


                    cli->Client->Send(name);



                }

            }

        }
        if (cli->Client->EventCount() == ec) {
            cli->Client->ClearEvents();
        }
        
        cli->Client->unlock();

    }

}


void GameClient::SetPlayerInfo(PlayerInfo* inf) {

    info = inf;

}

GameClient::GameClient(const char* ip, int port,PlayerInfo* inf) {

    info = inf;

	InitNetworking();

	printf("Starting client.\n");
	Client = new SyClient(ip, port);
	Client->Connect();
	printf("Client connected.\n");

	std::thread checkThr(Client_Thr, this);
	checkThr.detach();



}