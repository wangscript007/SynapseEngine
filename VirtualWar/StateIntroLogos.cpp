#include "StateIntroLogos.h"

void StateIntroLogos::InitState() {

	ui = new UI(VirtualWarApp::rWidth, VirtualWarApp::rHeight);

	Texture2D* bg = new Texture2D("game/vw/images/logo/logobg.jpg", false);
	Texture2D* ilogo1 = new Texture2D("game/vw/images/logo/logo1.png", true);
	Texture2D* ilogo2 = new Texture2D("game/vw/images/logo/logo2.png", true);
	Texture2D* ibar = new Texture2D("game/vw/images/logo/bar1.png",false);

	bar1 = new ImageControl(ibar);
	bar2 = new ImageControl(ibar);

	ImageControl* logo1 = new ImageControl(bg);
	clogo1 = new ImageControl(ilogo1);
	clogo2 = new ImageControl(ilogo2);



	logo1->Set(0, 0, VirtualWarApp::rWidth, VirtualWarApp::rHeight);
	clogo1->Set(0, 0, VirtualWarApp::rWidth, VirtualWarApp::rHeight);
	clogo2->Set(0, 256, VirtualWarApp::rWidth, 512);

	ui->GetRoot()->AddControl(logo1);
	ui->GetRoot()->AddControl(clogo1);
	ui->GetRoot()->AddControl(clogo2);
	ui->GetRoot()->AddControl(bar1);
	ui->GetRoot()->AddControl(bar2);

	logo1->SetColor(0, 0, 0, 0);
	clogo1->SetColor(0, 0, 0, 0);
	cbg = logo1;

	logoTrack = SoundEngine::Main->LoadSound("game/vw/sound/music/logo/logoTrack.mp3");

	logoChan = logoTrack->Play();

}

void StateIntroLogos::RenderState() {

	if (bgAlpha < 1.0f && f1==false)
	{

		bgAlpha = bgAlpha + 0.015f;
	}
	else {
		f1 = true;
		if (syAlpha < 1.0f) {
			syAlpha = syAlpha + 0.015f;
		}
		else {
			if (bgAlpha > 0.0f) {
				bgAlpha = bgAlpha - 0.015f;
				
			}
		}
		if (bgAlpha < 0.6f) {
			if (lx < 150.0f) {
				lx += 2.5f;
				if (enAlpha < 1.0f) {
					enAlpha += 0.02f;
				}
			}
		}
	}
	cbg->SetColor(bgAlpha, bgAlpha, bgAlpha, bgAlpha);
	clogo1->SetColor(syAlpha, syAlpha, syAlpha, syAlpha);
	clogo2->SetColor(enAlpha, enAlpha, enAlpha, enAlpha);
	clogo1->Set(lx-200, 100, VirtualWarApp::rWidth, VirtualWarApp::rHeight-240);

	bar1->Set(-300 + (lx*2) , 120, VirtualWarApp::rWidth - 128, 22);
	bar2->Set(VirtualWarApp::rWidth+(300-(lx*2)), 620, -(VirtualWarApp::rWidth-128), 22);
	bar1->SetColor(enAlpha, enAlpha, enAlpha, enAlpha);
	bar2->SetColor(enAlpha, enAlpha, enAlpha, enAlpha);

	ui->Update();

	ui->Render();

}