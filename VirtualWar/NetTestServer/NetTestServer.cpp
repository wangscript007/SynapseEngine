// NetTestClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SyHost.h"

int main()
{
    std::cout << "Hello World!\n";

    InitNetworking();

    SyHost* host = new SyHost(8888);

    while (true) {

        if (host->GetInUse()) {
            continue;
        }

        int ec = host->EventCount();

        for (int i = 0; i < ec; i++) {

            NetEvent evt = host->GetEvent(i);

            switch (evt.Type) {

            case NetEventType::NewMessage:

                auto msg = evt.Msg;

                std::string res = msg->PullString();

                printf("Client:");
                printf(res.c_str());
                printf("\n");

                auto rm = new NetMsg("say", 0, 256);
                rm->PushString(res);

                host->BroadCast(rm);

                    break;

            }

        }

        host->ClearEvents();


        /*
        for (int i = 0; i < host->PeerCount(); i++) {

            auto peer = host->GetPeer(i);

            if (peer->Msgs.size() > 0)
            {
                auto msg = peer->Msgs[0];
                peer->ClearMsgs();

                std::string res = msg->PullString();

                printf("Client:");
                printf(res.c_str());
                printf("\n");

                auto rm = new NetMsg("say", 0, 256);
                rm->PushString(res);

                host->BroadCast(rm);



            }

        }
        */
    }




}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
