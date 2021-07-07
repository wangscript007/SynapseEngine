#pragma once
#include<winsock2.h>
#include <vector>
#include <map>
#include "NetMsg.h"
struct RemotePeer {

	char* addr;
	USHORT port;
	sockaddr_in rpc;


	std::vector<NetMsg*> Msgs;
	std::map<std::string, std::vector<NetMsg*>> MMsgs;

	void ClearMsgs() {

		Msgs.resize(0);
		MMsgs.clear();


	}

};