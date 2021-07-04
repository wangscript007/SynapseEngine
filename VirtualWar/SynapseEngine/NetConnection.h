
class NetConnection
{
public:

	void CreateConnection(int port);

protected:
	int ires;
	int sock;

	const char* ConnectIP;
	const char* ConnectPort;
	int connectIP;
	int connectPort;
	
};

