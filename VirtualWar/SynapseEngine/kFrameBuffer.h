#pragma once
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "Texture2D.h"
#include <stdio.h>


class kFrameBuffer
{
public:
	kFrameBuffer(int w, int h);
	void bind();
	void unbind();
	Texture2D* getBB();

private:
	int fW, fH;
	GLuint id;
	GLuint rb;
	Texture2D* bb;
	Texture2D* db;

};

