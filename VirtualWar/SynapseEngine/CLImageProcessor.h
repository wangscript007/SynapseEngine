#pragma once
#include <CL/cl.hpp>

class CLImageProcessor
{
public:

	CLImageProcessor();
	void SetSource(const char* path);
	void SetSize(int w, int h,bool alpha = false);
	void SetKernal(const char* name);
	void SetImageBuffer(unsigned char* buf);
	void SetOutputBuffer(unsigned char* buf);
	void AddIntPar(int i, int v);
	void AddFloatPar(int i, float v);
	void RunKernel(int num,int num2);
	void Free();
private:

	const char* CLPath = "";
	int ImgW, ImgH;
	bool Alpha;
	const char* KernalName;
	cl::Program::Sources code;
	cl::Program program;
	unsigned char* ImgBuf;
	unsigned char* OutBuf;
	cl::Buffer CLImgBuf;
	cl::Buffer CLOutput;
	cl::CommandQueue CLQueue;
	cl::Kernel CLKernel;
	

};

