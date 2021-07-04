#include "NetServer.h"

NetServer::NetServer(int port) {

	connectPort = port;
	CreateConnection(port);

}