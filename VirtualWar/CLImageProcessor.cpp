#pragma once
#include "CLImageProcessor.h"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <istream>
#include <ostream>
#include <string.h>
#include <strstream>
#include <mmstream.h>
#include "VirtualWarApp.h"

CLImageProcessor::CLImageProcessor() {


}

void CLImageProcessor::SetSize(int w, int h,bool alpha) {

	ImgW = w;
	ImgH = h;
	Alpha = alpha;

}

void CLImageProcessor::Free() {


}

void CLImageProcessor::SetImageBuffer(unsigned char* buf) {

	ImgBuf = buf;

	int bpp = 3;
	if (Alpha) {
		bpp = 4;
	}

	CLImgBuf = cl::Buffer(VirtualWarApp::Main->GetCLContext(),CL_MEM_READ_ONLY,(size_t)(ImgW * ImgH * bpp));
	CLOutput = cl::Buffer(VirtualWarApp::Main->GetCLContext(),CL_MEM_READ_WRITE  , (size_t)(ImgW * ImgH * bpp));
	
	CLQueue.enqueueWriteBuffer(CLImgBuf, CL_TRUE, 0, (size_t)(ImgW * ImgH * bpp),buf);

	

}

void CLImageProcessor::SetSource(const char* src) {



	CLPath = src;
	std::ifstream t(src);
	std::stringstream buffer;
	buffer << t.rdbuf();

	auto cs = buffer.str();

	std::cout << "Source:" << std::endl << cs << std::endl;

	//code.push_back((const char*)/
		//cs.c_str());
	code.push_back({cs.c_str(), cs.length()});

	program = cl::Program(VirtualWarApp::Main->GetCLContext(), code);

	if (program.build({VirtualWarApp::Main->GetCLDevice() }) != CL_SUCCESS) {
		std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(VirtualWarApp::Main->GetCLDevice()) << "\n";
		exit(1);
	}

	CLQueue = cl::CommandQueue(VirtualWarApp::Main->GetCLContext(),VirtualWarApp::Main->GetCLDevice());


}

void CLImageProcessor::SetKernal(const char* name) {

	KernalName = name;
	CLKernel = cl::Kernel(program,name);
	CLKernel.setArg(0, CLImgBuf);
	CLKernel.setArg(1, CLOutput);
	CLKernel.setArg<int>(2, ImgW);
	CLKernel.setArg<int>(3, ImgH);
	//CLKernel.setArg<int>(4,)


}

void CLImageProcessor::SetOutputBuffer(unsigned char* buf) {

	OutBuf = buf;

}

void CLImageProcessor::RunKernel(int num, int num2)
{
	printf("Calling kernel.\n");
	CLQueue.enqueueNDRangeKernel(CLKernel, cl::NullRange, cl::NDRange(ImgW*ImgH), cl::NullRange);
	CLQueue.finish();
	printf("Kernel finished.\n");

	 cl_int r = CLQueue.enqueueReadBuffer(CLOutput, CL_TRUE, 0, (size_t)(ImgW * ImgH * 3), OutBuf);

	 CLQueue.finish();
	 if (r != CL_SUCCESS) {

		 printf("Output failed.\n");
	 }


}

void CLImageProcessor::AddIntPar(int i, int v) {

	CLKernel.setArg<int>(i, v);

}

void CLImageProcessor::AddFloatPar(int i, float v) {

	CLKernel.setArg<float>(i, v);

}