#pragma once
#include "TextureCube.h"
class FrameBufferCube
{
public:
	FrameBufferCube(int w, int h);
	int SetFace(int face);
	void Release();
	TextureCube* GetCube() {
		return Cube;
	}
private:
	GLuint FBO, FBD;
	GLuint W, H;
	TextureCube* Cube;
};


