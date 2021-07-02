#include "CLTransformer.h"


#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <istream>
#include <ostream>
#include <string.h>
#include <sstream>
#include <strstream>
#include <mmstream.h>
CLTransformer::CLTransformer() {

	CLMain::InitCL();

}

void CLTransformer::SetInput(glm::vec3* stream,int count,glm::mat4 mat) {

	vecStream = stream;
	vecCount = count;

	int inSize = count * (3 * 4);
	int mSize = sizeof(mat);
	
	if (!createdBuf) {
		CLInBuf = cl::Buffer(CLMain::GetContext(), CL_MEM_READ_ONLY, (size_t)(inSize));
		CLOutBuf = cl::Buffer(CLMain::GetContext(), CL_MEM_READ_WRITE, (size_t)(inSize));
		CLMatBuf = cl::Buffer(CLMain::GetContext(), CL_MEM_READ_ONLY, (size_t)(mSize));
		createdBuf = true;
	}

	CLQueue.enqueueWriteBuffer(CLInBuf, CL_TRUE, 0, (size_t)(inSize), stream);
	CLQueue.enqueueWriteBuffer(CLMatBuf, CL_TRUE, 0, (size_t)(mSize), &mat);


}

void CLTransformer::setMatrix(glm::mat4 mat) {

	streamMatrix = mat;

}

void CLTransformer::loadProgram() {

	const char* src = "data/cl/transformer/transform.cl";

	CLPath = src;
	std::ifstream t(src);
	std::stringstream buffer;
	buffer << t.rdbuf();

	auto cs = buffer.str();

	std::cout << "Source:" << std::endl << cs << std::endl;

	//code.push_back((const char*)/
		//cs.c_str());
	code.push_back({ cs.c_str(), cs.length() });

	program = cl::Program(CLMain::GetContext(), code);

	if (program.build({CLMain::GetDevice() }) != CL_SUCCESS) {
		std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(CLMain::GetDevice()) << "\n";
		exit(1);
	}

	CLQueue = cl::CommandQueue(CLMain::GetContext(),CLMain::GetDevice());


	CLKernel = cl::Kernel(program,"transform");


}

glm::vec3* CLTransformer::Transform() {

	CLKernel.setArg(0, CLInBuf);
	CLKernel.setArg(1, CLMatBuf);
	CLKernel.setArg(2, CLOutBuf);
	CLKernel.setArg<int>(3, vecCount);
	//CLKernel.setArg<int>(3, ImgH);

	printf("Calling kernel.\n");
	CLQueue.enqueueNDRangeKernel(CLKernel, cl::NullRange, cl::NDRange(vecCount), cl::NullRange);
	CLQueue.finish();
	printf("Kernel finished.\n");

	glm::vec3* outData = new glm::vec3[vecCount];

	cl_int r = CLQueue.enqueueReadBuffer(CLOutBuf, CL_TRUE, 0, (size_t)(vecCount*3*4), outData);

	CLQueue.finish();
	if (r != CL_SUCCESS) {

		printf("Output failed.\n");
	}
	else {

		printf("Done!\n");
	}
	return outData;
}