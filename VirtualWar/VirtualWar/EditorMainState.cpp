#include "EditorMainState.h"
#include "GameIncludes.h"
#include "EngineGlobal.h"
#include "UITheme.h"
#include "UITheme_Neon.h"
#include "StateTest1.h"
#include "StateTest2.h"
#include "StatePhysicsTest1.h"
#include "StateIntroLogos.h"
#include "StateRenderTest1.h"
#include "StateAnimationTest1.h"
#include "StateOctreeTest1.h"
#include "StateParticleTest1.h"
#include "StateFPSTest1.h"
#include "StateNetworkTest1.h"
#include "VirtualWarApp.h"



void EditorMainState::InitState() {

	printf("Starting main editor state.\n");
	ui = new UI(EngineGlobals::rWidth, EngineGlobals::rHeight);

	UI::Theme = new UITheme_Neon();

	ImageControl* bg = new ImageControl("game/alpha/alphabg1.png",false);

	bg->Set(0, 0, EngineGlobals::rWidth, EngineGlobals::rHeight);


	ButtonControl* begin = new ButtonControl();

	ButtonControl* test2 = new ButtonControl();

	ButtonControl* pyTest = new ButtonControl();

	ButtonControl* logoSeq = new ButtonControl();
	
	ButtonControl* gameRender = new ButtonControl();

	ButtonControl* animTest1 = new ButtonControl();

	ButtonControl* octreeTest1 = new ButtonControl();

	ButtonControl* particleTest1 = new ButtonControl();

	ButtonControl* fpsTest1 = new ButtonControl();

	ButtonControl* netTest1 = new ButtonControl();

	netTest1->Set(230, 400, 200, 25);
	netTest1->SetText("Network Test 1");
	fpsTest1->Set(230, 320, 200, 25);
	fpsTest1->SetText("FPS Control Test");
	particleTest1->Set(20, 320, 200, 25);
	particleTest1->SetText("Particle System Test");
	octreeTest1->Set(20, 280, 200, 25);
	octreeTest1->SetText("Octree Test 1");
	animTest1->Set(230, 235, 200, 25);
	animTest1->SetText("Animation Test 1");
	test2->Set(20, 239, 200, 25);
	begin->Set(20, 200,200, 25);
	gameRender->Set(440, 240, 200, 25);
	logoSeq->Set(440, 200, 200, 25);
	begin->SetText("GameWorld Test 1");
	test2->SetText("GameWorld Test 2");
	gameRender->SetText("InGame Renderer");
	pyTest->Set(230, 200, 200, 25);
	pyTest->SetText("Physics Test 1");
	logoSeq->SetText("Logo Sequence");
	bg->AddControl(begin);
	bg->AddControl(test2);
	bg->AddControl(gameRender);
	bg->AddControl(pyTest);
	bg->AddControl(logoSeq);
	bg->AddControl(animTest1);
	bg->AddControl(octreeTest1);
	bg->AddControl(particleTest1);
	bg->AddControl(fpsTest1);
	bg->AddControl(netTest1);


	auto act_NetTest1 = [&]
	{

		StateNetworkTest1* nt1 = new StateNetworkTest1;
		VirtualWarApp::PushState(nt1);

	};

	auto act_FpsTest1 = [&]
	{

		StateFPSTest1* fps1 = new StateFPSTest1;
		VirtualWarApp::PushState(fps1);

	};

	auto act_Particle1 = [&] {

		StateParticleTest1* pt1 = new StateParticleTest1;
		VirtualWarApp::PushState(pt1);

	};

	auto act_Begin1 = [&] {

		StateTest1* t1 = new StateTest1;
		VirtualWarApp::PushState(t1);


	};

	auto act_Test2 = [&] {

		StateTest2* t2 = new StateTest2;
		VirtualWarApp::PushState(t2);

	};

	auto act_pyTest = [&] {

		StatePhysicsTest1* fp = new StatePhysicsTest1;
		VirtualWarApp::PushState(fp);

	};

	auto act_LogoSeq = [&] {

		StateIntroLogos* logos = new StateIntroLogos;
		VirtualWarApp::PushState(logos);

	};

	auto act_GameRender = [&] {


		StateRenderTest1* rt1 = new StateRenderTest1;
		VirtualWarApp::PushState(rt1);

	};

	auto act_AnimTest1 = [&]
	{

		StateAnimationTest1* at1 = new StateAnimationTest1;
		VirtualWarApp::PushState(at1);

	};

	auto act_octreeTest1 = [&]
	{

		StateOctreeTest1* ot1 = new StateOctreeTest1;
		VirtualWarApp::PushState(ot1);

	};

	netTest1->SetAction(act_NetTest1);
	octreeTest1->SetAction(act_octreeTest1);
	begin->SetAction(act_Begin1);
	test2->SetAction(act_Test2);
	pyTest->SetAction(act_pyTest);
	logoSeq->SetAction(act_LogoSeq);
	gameRender->SetAction(act_GameRender);
	animTest1->SetAction(act_AnimTest1);
	particleTest1->SetAction(act_Particle1);
	fpsTest1->SetAction(act_FpsTest1);
	

	ui->GetRoot()->AddControl(bg);

}

void EditorMainState::UpdateState() {

	ui->Update();

}

void EditorMainState::RenderState() {

	ui->Render();

}