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
	int PullInt();
	float PullFloat();
	short PullShort();
	double PullDouble();
	char PullChar();
	std::string PullString();

	char* GetBuf();
	int GetSize();
	std::string GetChannel();
	int GetAck();
private:
	std::string chan;
	int ack = 0;
	char* buf;
	short size = 0;
	short pos;
//	RemotePeer* intended;
};

