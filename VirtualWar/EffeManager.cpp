#include "EffeManager.h"
#include "VirtualWarApp.h"
#include <EffekseerRendererGL.h>

::EffekseerRendererGL::RendererRef renderer;

EffeManager::EffeManager() {

	renderer = ::EffekseerRendererGL::Renderer::Create(8000, EffekseerRendererGL::OpenGLDeviceType::OpenGL3);
	manager = ::Effekseer::Manager::Create(8000);
	manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
	manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
	manager->SetRingRenderer(renderer->CreateRingRenderer());
	manager->SetTrackRenderer(renderer->CreateTrackRenderer());
	manager->SetModelRenderer(renderer->CreateModelRenderer());
	manager->SetTextureLoader(renderer->CreateTextureLoader());
	manager->SetModelLoader(renderer->CreateModelLoader());
	manager->SetMaterialLoader(renderer->CreateMaterialLoader());
	manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());




}

void EffeManager::SetCam(NodeCam* cam) {

	renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovRH_OpenGL(45.0f / 180.0f * 3.14f, (float)VirtualWarApp::rWidth / (float)VirtualWarApp::rHeight,cam->GetMinZ(),cam->GetMaxZ()));

	::Effekseer::Matrix44 cm = ::Effekseer::Matrix44().Indentity();

//	cm.V//alues[0][0] = 



		auto wm = cam->GetWorld();

		
		
		glm::vec4 r1, r2, r3, r4;

		r1 = wm[0];
		r2 = wm[1];
		r3 = wm[2];
		r4 = wm[3];

		cm.Values[0][0] = r1.x;
		cm.Values[0][1] = r1.y;
		cm.Values[0][2] = r1.z;
		cm.Values[0][3] = r1.w;

		cm.Values[1][0] = r2.x;
		cm.Values[1][1] = r2.y;
		cm.Values[1][2] = r2.z;
		cm.Values[1][3] = r2.w;

		cm.Values[2][0] = r3.x;
		cm.Values[2][1] = r3.y;
		cm.Values[2][2] = r3.z;
		cm.Values[2][3] = r3.w;

		cm.Values[3][0] = r4.x;
		cm.Values[3][1] = r4.y;
		cm.Values[3][2] = r4.z;
		cm.Values[3][3] = r4.w;

		//wm[0] = glm::vec4(cm.Values[0][0],cm.Values[0][1],cm.Values[0][2])


		//wm[0] = cm.Values[0][0];

	
		//glm::mat4(cm.Values[0][0], cm.Values[0][1], cm.Values[0][2], cm.Values[0][3],
		//	cm.Values[1][0], cm.Values[1][1], cm.Values[1][2], cm.Values[1][3],
		//	cm.Values[2][0], cm.Values[2][1], cm.Values[2][2], cm.Values[2][3],
		//	cm.Values[3][0], cm.Values[3][1], cm.Values[3][2], cm.Values[3][3]);
		// 視点位置を確定
		auto g_position = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

		renderer->SetCameraMatrix(cm);

	//renderer->SetCameraMatrix(
	//	::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));



}

EffeFX* EffeManager::LoadFX(const char16_t* path) {

	EffeFX* fx = new EffeFX;

	fx->ref = Effekseer::Effect::Create(manager,path);

	return fx;
}

EffeHandle* EffeManager::Play(EffeFX* fx,glm::vec3 pos) {

	EffeHandle* h = new EffeHandle;

	h->handle = manager->Play(fx->ref, pos.x,pos.y,pos.z);

	return h;


}

void EffeManager::Stop(EffeHandle* h) {

	manager->StopEffect(h->handle);

}

void EffeManager::update() {

	manager->Update(0.05f);

}

void EffeManager::render() {

	renderer->BeginRendering();
	//renderer->

	// Render effects
	// エフェクトの描画を行う。
	manager->Draw();

	// Finish to rendering effects
	// エフェクトの描画終了処理を行う。
	renderer->EndRendering();


}