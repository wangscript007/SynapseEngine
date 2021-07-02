#pragma once
#include<iostream>
#include<ostream>
#include<fstream>
#include "glm/glm.hpp"
//#include "Vec2.h"

enum FileMode {

	Write,Read

};

class VFile
{
public:
	static bool Exists(const char* path);

	VFile(const char* path, FileMode mode);
	void WriteInt(int v);
	void WriteFloat(float v);
	void WriteString(const char* str);
	void WriteByte(char b);
	void WriteBytes(void* data, int length);
	void WriteBool(bool b);
	void WriteVec3(glm::vec3 v);
	glm::vec3 ReadVec3();
	//void WriteVec3(Vec3 v);
	void WriteLong(long v);

//	Vec3 ReadVec3();

	int ReadInt();
	float ReadFloat();
	char ReadByte();
	void* ReadBytes(int len);
	const char* ReadString();
	long ReadLong();
	bool ReadBool();
	void Close();
	static long Length(const char * path);

private:
	std::ifstream istream;
	std::ofstream ostream;
	FileMode mod;
	int readPos = 0;

};

