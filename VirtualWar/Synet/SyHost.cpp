#include "SyHost.h"

void HostThread(SyHost* host) {

	while (true) {

		host->CheckNet();

	}

}

SyHost::SyHost(int port) {


	



	slen = sizeof(si_other);

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons((u_short)port);

	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");


	std::thread load(HostThread, this);
	load.detach();

}

void SyHost::CheckNet() {
    
	InUse = true;
	//printf("Waiting for data...");
	fflush(stdout);

	//clear the buffer by filling null, it might have previously received data
	memset(buf, '\0', BUFLEN);


	InUse = true;
	//try to receive some data, this is a blocking call
	if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
	{
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}


	//InUse = true;


	NetMsg* msg = new NetMsg(buf, BUFLEN);
		
	//printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

	if (HasPeer(inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port)))
	{


	//	std::string res = msg->PullString();

		auto rp = FindPeer(inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		rp->Msgs.push_back(msg);

		auto nme = NetEvent(NetEventType::NewMessage);
		nme.Msg = msg;
		nme.Peer = rp;

		PushEvent(nme);

	//	rp->MMsgs[msg->GetChannel()].push_back(msg);

		//int tm = msg->PullInt();


	//	printf("New message from established peer.\n");

	}else{


		//int code = msg->PullInt();

	//	printf("Connect Msg:");
	//	printf(msg->PullString().c_str());
	//	printf("\n");

		int ccode = msg->PullInt();


		printf("Connect Code:%d \n", ccode);

		RemotePeer* new_peer = new RemotePeer;
		new_peer->addr = inet_ntoa(si_other.sin_addr);
		new_peer->port = ntohs(si_other.sin_port);
		new_peer->rpc = si_other;
		AddPeer(new_peer);
		printf("Added peer.\n");
		printf("Connect request Len:%d\n", recv_len);
	
		auto nce = NetEvent(NetEventType::NewClientConnected);
		nce.Peer = new_peer;

		PushEvent(nce);

	}

	//printf("Data: %s\n", buf);

	//now reply the client with the same data
	/**/

	/*
	if (sendto(s, buf, recv_len, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	//*/
	InUse = false;
}

void SyHost::AddPeer(RemotePeer* peer) {

	peers.push_back(peer);

}

RemotePeer* SyHost::FindPeer(char* ip, USHORT port) {

	for (int p = 0; p < peers.size(); p++) {

		auto rp = peers[p];
		if (std::string(ip) == std::string(rp->addr)) {

			if (port == rp->port) {
				return rp;
			}

		}
	}
	return nullptr;
}

bool SyHost::HasPeer(char* ip, USHORT port) {

	for (int p = 0; p < peers.size(); p++) {

		auto rp = peers[p];
		if (std::string(ip) == std::string(rp->addr)) {

			if (port == rp->port) {
				return true;
			}

		}
	}
	return false;
}


void SyHost::Send(char* buf, int len, RemotePeer* peer)
{
	if (sendto(s, buf, len, 0, (struct sockaddr*)&peer->rpc, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Sent to peer.\n");
}

void SyHost::BroadCast(NetMsg* msg) {

	for (int i = 0; i < peers.size(); i++) {

		auto peer = peers[i];

		Send(msg->GetBuf(), msg->GetSize(), peer);


	}

}