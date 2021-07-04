#include "CLMain.h"
#include <iostream>

bool CLMain::CLInit = false;
cl::Device CLMain::clDevice = NULL;
cl::Context CLMain::clContext = NULL;
cl::Platform CLMain::clPlatform = NULL;

void CLMain::InitCL() {

	if (CLInit) return;

	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if (all_platforms.size() == 0) {
		std::cout << " No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform default_platform = all_platforms[0];
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if (all_devices.size() == 0) {
		std::cout << " No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Device default_device = all_devices[0];
	std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";
	clPlatform = default_platform;
	clDevice = default_device;

	clContext = cl::Context(clDevice);

	CLInit = true;

}