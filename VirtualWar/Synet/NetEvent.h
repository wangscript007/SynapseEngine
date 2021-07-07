#pragma once
#include "RemotePeer.h"
#include "NetMsg.h"
enum NetEventType {

	NewClientConnected,ConnectedToHost,NewMessage,None

};

struct NetEvent {

	NetEventType Type;
	RemotePeer* Peer;
	NetMsg* Msg;

	NetEvent() {

		Type = NetEventType::None;
		Peer = nullptr;
		Msg = nullptr;

	}
	NetEvent(NetEventType t) {

		Type = t;
		Peer = nullptr;
		Msg = nullptr;

	}


};

