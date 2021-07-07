#include "UITheme_Neon.h"
#include "Texture2D.h"
#include "UI.h"
UITheme_Neon::UITheme_Neon() {


	ButTop = new Texture2D("UI/Neon/ButTop.png", true);

	ButDown = new Texture2D("UI/Neon/ButDown.png", true);
	ButLeft = new Texture2D("UI/Neon/ButLeft.png", true);
	ButRight = new Texture2D("UI/Neon/ButRight.png", true);

	ButLeftTop = new Texture2D("UI/Neon/butlefttop.png", true);
	ButLeftDown = new Texture2D("UI/Neon/ButLeftDown.png", true);
		
	ButRightTop = new Texture2D("UI/Neon/butrighttop.png", true);
	ButRightDown = new Texture2D("UI/Neon/Butrightdown.png", true);
	
	ButMid = new Texture2D("UI/Neon/buttongrey1.png", true);

	FrameBG = new Texture2D("UI/Neon/butmid.png", true);



	//while (true) {};

};

void UITheme_Neon::DrawButton(int x, int y, int w, int h, const char* text,bool over,bool pressed)
{

	if (pressed) {
		//DrawDyanmicBox(x, y, w, h, ButTop, ButDown, ButLeft, ButRight, ButLeftTop, ButLeftDown, ButRightTop, ButRightDown, ButMid, 0.8, 1, 1, 1);
		DrawImg(x, y, w, h, ButMid, 0.8f, 1, 1, 1);
	}else if (over) {
		//DrawDyanmicBox(x, y, w, h, ButTop, ButDown, ButLeft, ButRight, ButLeftTop, ButLeftDown, ButRightTop, ButRightDown, ButMid, 0.6f, 0.9f, 0.9f, 1);
		DrawImg(x, y, w, h, ButMid, 0.6f, 0.9f, 0.9f, 1.0f);
	}
	else {
		//DrawDyanmicBox(x, y, w, h, ButTop, ButDown, ButLeft, ButRight, ButLeftTop, ButLeftDown, ButRightTop, ButRightDown, ButMid, 0.5f, 0.7f, 0.7f, 1);
		DrawImg(x, y, w, h, ButMid, 0.5f, 0.7f, 0.7f, 1.0f);
	}
	//printf(text);
	//
//	printf(text);
	//printf("W:%d H:%D tw:%d", w, 0, UI::TextWidth(text));
	//printf("\n");

	UI::RenderText(x + w / 2 - (UI::TextWidth(text) / 2), y + h / 2 - (UI::TextHeight(text)/2), text, 1, 1, 1, 1);


};



void UITheme_Neon::DrawFrame(int x, int y, int w, int h,float r,float g,float b,float a) {

	UI::DrawTexture(FrameBG, x, y, w, h, r, g, b, a);


}