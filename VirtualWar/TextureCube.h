#pragma once
#include "VirtualWarApp.h"
class TextureCube
{
public:
	TextureCube(int w, int h);
	void Bind(int unit);
	void Release(int unit);
	GLuint GetID() {
		return ID;
	}
private:
	int W, H;
	int D;
	GLuint ID;
};


