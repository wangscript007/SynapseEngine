// NetTestClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SyClient.h"
#include <thread>
#include <string>


void msg_thread(SyClient* cli1) {

    while (true) {

        int mc = cli1->MsgCount();

        if (mc > 0) {

            NetMsg* gm = cli1->GetMsg(0);

            if (gm->GetChannel() == "say")
            {
                std::string said = gm->PullString();

                printf("Someone said:");
                printf(said.c_str());
                printf("\n");
            }

            cli1->ClearMsgs();

        }
        Sleep(25);

    }

}

int main()
{
    std::cout << "Hello World!\n";

    InitNetworking();



    SyClient* cli1 = new SyClient("127.0.0.1", 8888);

    cli1->Connect();

    int lack = 0;

    std::thread checkThr(msg_thread, cli1);
    checkThr.detach();


    while (true) {

        std::string say;

        std::getline(std::cin, say);

        //std::cin >> say;
        

        if (say.length() > 1)
        {
            printf("Sending message:");
            printf(say.c_str());
            printf("\n");
            NetMsg* sm = new NetMsg("say", lack, 512);
            sm->PushString(say);
            cli1->Send(sm);
            say = "";

        }

       

        Sleep(1000);

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
