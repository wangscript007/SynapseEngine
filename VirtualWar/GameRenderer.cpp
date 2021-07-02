#include "GameRenderer.h"
#include "VirtualWarApp.h"

GameRenderer::GameRenderer() {

	fx_bloom = new ppBloom();
	fx_ssr = new ppSSR();
	frame_world = new kFrameBuffer(VirtualWarApp::rWidth, VirtualWarApp::rHeight);


	//while(true){ }
}

void GameRenderer::SetWorld(GameWorld* gworld) {

	world = gworld;
	fx_ssr->cam = gworld->GetCam();
	drawer = new IDraw(VirtualWarApp::rWidth,VirtualWarApp::rHeight);

}


void GameRenderer::Render() {

	
	world->RenderShadows();
	
	world->RenderToFB();
	
	world->RenderMaps();

	auto maps = world->GetMaps();

	fx_ssr->SetMaps(maps);

	auto rtex = fx_ssr->process(NULL);

	
	frame_world->bind();

	drawer->Begin();
	drawer->DrawTex(0, VirtualWarApp::rHeight, VirtualWarApp::rWidth,-VirtualWarApp::rHeight, maps[0]->getBB(), 1, 1, 1, 1);
	drawer->End();

	//frame_world->unbind();
	
	

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);


	drawer->Begin();
	drawer->DrawTex(0, 0, VirtualWarApp::rWidth, VirtualWarApp::rHeight, rtex, 1, 1, 1, 1);
	drawer->EndNoBlend();

	frame_world->unbind();
	

	//world->RenderNormals();
	//drawer->Begin();
	//drawer->DrawTex(0, 0, 256, 256, maps[2]->getBB(), 1, 1, 1, 1);
	//drawer->End();





	rtex = fx_bloom->process(frame_world->getBB());
	//o rtex = fx_ssr->process(frame_world->getBB());
	//rtex = maps[0]->getBB();

	drawer->Begin();
	drawer->DrawTex(0,VirtualWarApp::rHeight,VirtualWarApp::rWidth,-VirtualWarApp::rHeight,rtex, 1, 1, 1, 1);
	drawer->End();


	//fx_bloom->process(frame_world->getBB());


}