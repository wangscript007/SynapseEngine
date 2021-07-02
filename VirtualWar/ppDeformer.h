#pragma once
#include "kFrameBuffer.h"
#include "kPostProcess.h"
class ppDeformer : kPostProcess
{
public:
	ppDeformer(kamGame * g) {

		game = g;
		fb1 = new kFrameBuffer(g->getW(), g->getH());
		fb2 = new kFrameBuffer(g->getW(), g->getH());
		waveFx = new kEffect("data/shader/pp/deformer/deformVertex.glsl", "data/shader/pp/deformer//deformFrag.glsl");

	}
	void beginDeform() {
		
		fb1->bind();
		glClearColor(0.5, 0.5, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void paint(kImage* img,int x,int y,int w,int h) {

		game->drawImg(x-w/2, y-h/2, w, h, 1, 1, 1, 1, img);

	}

	kImage* getBB() {

		return fb1->getBB();

	}

	void endDeform() {

		fb1->unbind();

	}

	kImage* process(kImage* base)
	{

		fb2->bind();
		waveFx->bind();
		waveFx->setInt("fb", 0);
		waveFx->setInt("deform", 1);

		fb1->getBB()->bind(1);


		game->drawImg(0, 0, game->getW(), game->getH(), 1, 1, 1, 1, base);

		fb1->getBB()->release(1);

		waveFx->unbind();
		fb2->unbind();

		return fb2->getBB();

	}
private:
	kFrameBuffer* fb1;
	kFrameBuffer* fb2;
	kEffect* waveFx;
	kamGame* game;
};

