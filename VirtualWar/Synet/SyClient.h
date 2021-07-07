#pragma once
#include "SyConnection.h"
class SyClient : public SyConnection
{
public:

	SyClient(const char* ip, int port);
	void Update();
	void Connect();
	void Send(char* data, int len);
	void Send(NetMsg* msg);
	int GetAck();
	void CheckNet();
	int MsgCount();
	NetMsg* GetMsg(int id);
	void ClearMsgs();
private:

	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;
	std::vector<NetMsg*> Msgs;
	int cAck = 0;

};

