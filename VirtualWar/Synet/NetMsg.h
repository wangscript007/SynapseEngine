#pragma once
#include <string>
class NetMsg
{
public:

	NetMsg(std::string chan,int ack,char* buf, int len);
	NetMsg(std::string chan,int ack,int maxBuf);
	NetMsg(char* buf, int bsize);
	void PushInt(int v);
	void PushFloat(float v);
	void PushShort(short v);
	void PushDouble(double v);
	void PushChar(char v);
	void PushString(std::string v);
	void PushLong(long v);
	int PullInt();

	float PullFloat();
	short PullShort();
	double PullDouble();
	char PullChar();
	std::string PullString();
	long PullLong();

	char* GetBuf();
	int GetSize();
	std::string GetChannel();
	int GetAck();
	int GetPos() {
		return pos;
	}
private:
	std::string chan;
	int ack = 0;
	char* buf;
	int size = 0;
	int pos;
//	RemotePeer* intended;
};

