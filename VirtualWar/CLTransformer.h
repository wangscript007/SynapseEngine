#pragma once
#include "CLMain.h"
#include "glm/glm.hpp"


class CLTransformer
{
public:
	CLTransformer();
	void SetInput(glm::vec3* input, int count,glm::mat4 mat);
	void setMatrix(glm::mat4 mat);
	void loadProgram();
	glm::vec3* Transform();

private:
	cl::Program::Sources code;
	cl::Program program;
	bool createdBuf = false;
	cl::Buffer CLInBuf;
	cl::Buffer CLOutBuf;
	cl::Buffer CLMatBuf;
	cl::CommandQueue CLQueue;
	cl::Kernel CLKernel;
	glm::vec3* vecStream;
	glm::mat4 streamMatrix;
	int vecCount;
	const char* CLPath = "";

};

