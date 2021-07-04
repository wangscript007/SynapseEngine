#pragma once
#include <CL/cl.hpp>

class CLMain
{
public:

	static void InitCL();

	static cl::Platform GetPlatform() {
		return clPlatform;
	}

	static cl::Device GetDevice() {
		return clDevice;
	}

	static cl::Context GetContext() {
		return clContext;
	}

private:
	static bool CLInit;
	static cl::Platform clPlatform;
	static cl::Device clDevice;
	static cl::Context clContext;
};


