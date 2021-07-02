#include "ppSSR.h"
#include "VirtualWarApp.h"
ppSSR::ppSSR() {

	ssrFinal =  new kEffect("data/shader/pp/ssr/ssrFinalVert.glsl", "data/shader/pp/ssr/ssrFinalFrag.glsl");
	//while(true){}

	maps.resize(0);

}

void ppSSR::SetMaps(std::vector<kFrameBuffer*> ms) {
	maps = ms;
}

Texture2D* ppSSR::process(Texture2D* tex)
{

	int bw, bh;

	bw = VirtualWarApp::rWidth;
	bh = VirtualWarApp::rHeight;

	if (fb1 == NULL) {

		fb1 = new kFrameBuffer(bw, bh);
		fb2 = new kFrameBuffer(bw, bh);
	}

	fb1->bind();

	ssrFinal->bind();
	float pw = VirtualWarApp::rWidth;
	float ph = VirtualWarApp::rHeight;
	glm::mat4 pMat = glm::ortho((float)0, (float)pw, (float)ph, (float)0, (float)-100, (float)100);
	//ssrFinal->setInt("fb", 0);
	//ssrFinal->setFloat("tH", 0.5);

	glm::mat4 cam_view = cam->GetWorld();
	glm::mat4 cam_invView = glm::inverse(cam_view);
	glm::mat4 cam_invProj = glm::inverse(pMat);

	
	ssrFinal->setMat("view", cam_view);
//	ssrFinal->setMat("invprojection", cam_invProj);
//	ssrFinal->setMat("projection", pMat);
//	ssrFinal->setMat("invView", cam_invView);
	ssrFinal->setMat("proj", pMat);
	ssrFinal->setMat("camproj", cam->GetProj());
	ssrFinal->setInt("gFinalImage", 0);
	ssrFinal->setInt("gPosition", 1);
	ssrFinal->setInt("gNormal", 2);
	ssrFinal->setInt("gExtra", 3);

	maps[1]->getBB()->Bind(1);
	maps[2]->getBB()->Bind(2);
	maps[4]->getBB()->Bind(3);

	DrawImage(0, 0, bw, bh, 1, 1, 1, 1,maps[0]->getBB());

	maps[4]->getBB()->Release(3);
	maps[2]->getBB()->Release(2);
	maps[1]->getBB()->Release(1);

	//getGame()->drawImg(0, 0, getGame()->getW(), getGame()->getH(), 1, 1, 1, 1, base);

	ssrFinal->unbind();

	fb1->unbind();

	return fb1->getBB();

}