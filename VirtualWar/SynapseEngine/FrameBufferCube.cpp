#include "pch.h"
#include "FrameBufferCube.h"

FrameBufferCube::FrameBufferCube(int w, int h) {

	W = w;
	H = h;
	Cube = new TextureCube(w, h);

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glGenRenderbuffers(1, &FBD);

	glBindRenderbuffer(GL_RENDERBUFFER, FBD);

	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT16, w, h);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, Cube->GetID(), 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, FBD);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, Cube->GetID(), 0);
	//glBindFrameBuffer(GL_FRAMEBUFFER, FBO);
	
	int rc = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(rc!= GL_FRAMEBUFFER_COMPLETE)
	{
		printf("Framebuffer incomplete.\n");
		printf("Val:%d\n", rc);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	Cube->Release(0);






}

void FrameBufferCube::Release()
{

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

int FrameBufferCube::SetFace(int face) {

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, W, H);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, Cube->GetID(), 0);
	int af = (int)GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	return af;

}