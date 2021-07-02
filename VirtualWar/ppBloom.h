#pragma once
#include "kPostProcess.h"
#include "kFrameBuffer.h"

class ppBloom : public kPostProcess
{
public:

	ppBloom();

	Texture2D* process(Texture2D * base);

private:
	kEffect* getLight;
	kEffect* blurImg;
	kEffect* finalBloom;
	kFrameBuffer* fb1 = NULL;
	kFrameBuffer* fb2 = NULL;


};

