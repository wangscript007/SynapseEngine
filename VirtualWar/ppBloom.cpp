#include "ppBloom.h"
#include "VirtualWarApp.h"
ppBloom::ppBloom() {

	getLight = new kEffect("data/shader/pp/bloom/getLightVertex.glsl", "data/shader/pp/bloom/getLightFrag.glsl");
	blurImg = new kEffect("data/shader/pp/bloom/blurImgVertex.glsl", "data/shader/pp/bloom/blurImgFrag.glsl");
	finalBloom = new kEffect("data/shader/pp/bloom/finalBloomVertex.glsl", "data/shader/pp/bloom/finalBloomFrag.glsl");

	
}

Texture2D* ppBloom::process(Texture2D *base) {

	int bw, bh;

	bw = VirtualWarApp::rWidth;
	bh = VirtualWarApp::rHeight;

	if (fb1 == NULL) {

		fb1 = new kFrameBuffer(bw, bh);
		fb2 = new kFrameBuffer(bw,bh);
	}

	fb1->bind();

	getLight->bind();
	float pw = VirtualWarApp::rWidth;
	float ph = VirtualWarApp::rHeight;
	glm::mat4 pMat = glm::ortho((float)0, (float)pw, (float)ph, (float)0, (float)-100, (float)100);
	getLight->setInt("fb", 0);
	getLight->setFloat("tH", 0.6f);
	getLight->setMat("proj", pMat);

	DrawImage(0, 0, bw, bh, 1, 1, 1, 1, base);

	//getGame()->drawImg(0, 0, getGame()->getW(), getGame()->getH(), 1, 1, 1, 1, base);

	getLight->unbind();

	fb1->unbind();

	//n fb1->getBB();

	//return fb1->getBB();
	// fb1->getBB();


	fb2->bind();

	blurImg->bind();

	blurImg->setInt("fb", 0);

	blurImg->setFloat("blur", 0.01f);
	blurImg->setMat("proj", pMat);
	DrawImage(0, 0, bw, bh, 1, 1, 1, 1, fb1->getBB());
	//getGame()->drawImg(0, 0, getGame()->getW(), getGame()->getH(), 1, 1, 1, 1, fb1->getBB());

	blurImg->unbind();

	fb2->unbind();

	//return fb2->getBB();


	fb1->bind();

	finalBloom->bind();

	finalBloom->setInt("fb", 0);
	finalBloom->setInt("blur", 1);
	finalBloom->setMat("proj", pMat);
	
	fb2->getBB()->Bind(1);

	//getGame()->drawImg(0, 0, getGame()->getW(), getGame()->getH(), 1, 1, 1, 1,base);
	DrawImage(0, 0, bw, bh, 1, 1, 1, 1, base);

	fb2->getBB()->Release(1);

	finalBloom->unbind();

	fb1->unbind();

	return fb1->getBB();

	//getGame()->drawImg(0, 0, getGame()->getW()/2, getGame()->getH()/2, 1, 1, 1, 1,fb2->getBB());



}