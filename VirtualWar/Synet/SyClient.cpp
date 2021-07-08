#include "SyClient.h"
#include<stdio.h>
#include<thread>
void ClientThread(SyClient* cli) {

	while (true) {

		cli->CheckNet();

		Sleep(10);

	}

}

void SyClient::CheckNet() {

	fflush(stdout);

	//clear the buffer by filling null, it might have previously received data
	memset(buf, '\0', BUFLEN);

	int recv_len = 0;

	//try to receive some data, this is a blocking call
	if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
	{
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	gm.lock();
	printf("Client got message\n");

	NetMsg* msg = new NetMsg(buf, BUFLEN);

	if (msg->GetAck() < rAck) {
		return;
	}
	else {
		rAck++;
	}

	Msgs.push_back(msg);
	NetEvent ne = NetEvent(NetEventType::NewMessage);
	ne.Msg = msg;
	PushEvent(ne);
	gm.unlock();



}

int SyClient::MsgCount() {

	return Msgs.size();

}

NetMsg* SyClient::GetMsg(int id) {

	return Msgs[id];

}

void SyClient::ClearMsgs() {

	Msgs.resize(0);

}

SyClient::SyClient(const char* ip, int port) {

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons((u_short)port);
	si_other.sin_addr.S_un.S_addr = inet_addr(ip);

	//printf("Client established.\n");

	std::thread ClientThr(ClientThread, this);
	ClientThr.detach();

}

void SyClient::Connect() {

	char* sdat = new char[12];

	sdat[0] = 0;
	sdat[1] = 2;
	sdat[2] = 0;
	sdat[3] = 3;

	NetMsg* msg = new NetMsg("internal",GetSendAck(),255);

	msg->PushInt(254);

//	msg->PushString("This is a test msg.\n");

	Send(msg);

}

int SyClient::GetAck() {

	//cAck++;
	//return cAck-1;
	sAck++;
	return sAck-1;

}

void SyClient::Send(NetMsg* msg) {

	Send(msg->GetBuf(), msg->GetPos());

}

void SyClient::Send(char* buf, int len) {

	if (sendto(s, buf,len, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

}

void SyClient::Update() {

	
	//receive a reply and print it
	//clear the buffer by filling null, it might have previously received data
	memset(buf, '\0', BUFLEN);
	//try to receive some data, this is a blocking call
	if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen) == SOCKET_ERROR)
	{
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	NetMsg* m1 = new NetMsg(buf, BUFLEN);

	if (m1->GetAck() < rAck) {

		return;

	}
	rAck++;

	Msgs.push_back(m1);






}