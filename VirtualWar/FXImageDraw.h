#pragma once
#include "kEffect.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class FXImageDraw : public kEffect
{
public:

	FXImageDraw(int w,int h);
	void setPars();

private:
	int pw, ph;
	GLuint p1, p2, p3, p4;
	bool gotPars = false;

};

