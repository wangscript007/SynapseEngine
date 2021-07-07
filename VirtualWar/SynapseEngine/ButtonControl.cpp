#include "ButtonControl.h"
#include "UI.h"
#include "Texture2D.h"
#include "UITheme.h"


ButtonControl::ButtonControl() {

	Back = new Texture2D("UI/Neon/buttongrey1.png", true);
	Over = false;
	Pressed = false;
	ControlAble = true;
};

void ButtonControl::Render() {

	if (Icon != NULL) {
		float r, g, b, a;
		r = 0.7f;
		g = 0.7f;
		b = 0.7f;
		a = 1.0f;

		if (Over) {
			r = 0.85f;
			g = 0.85f;
			b = 0.85f;
			
		}

		if (Pressed)
		{
			r = 1;
			g = 1;
			b = 1;
		}

		UI::Theme->DrawImg(GetX(), GetY(), GetW(), GetH(), Back, r,g,b,a);
		if (Highlight)
		{
			UI::Theme->DrawFrame(GetX(), GetY(), GetW(), 3, 0, 2, 2, 1);
			UI::Theme->DrawFrame(GetX(), GetY(), 3, GetH(), 0, 2, 2, 1);
			UI::Theme->DrawFrame(GetX(), GetY() + GetH() - 3, GetW(), 3, 0, 2, 2, 1);
			UI::Theme->DrawFrame(GetX() + GetW() - 3, GetY(), 3, GetH(), 0, 2, 2, 1);
		}
		UI::Theme->DrawImg(GetX() + 5, GetY() + 2, GetW() - 10, GetH() - 4, Icon, r,g,b,a);
	}
	else {
		UI::Theme->DrawButton(GetX(), GetY(), GetW(), GetH(), GetText(), Over, Pressed);
	}
	//UI::DrawTexture(Back, GetX(), GetY(), GetW(),GetH(), 1, 1, 1, 1);
	
};

void ButtonControl::MouseEnter() {
	Over = true;
};

void ButtonControl::MouseLeave() {

	Over = false;

};

void ButtonControl::MouseDown(int b) {
	//exit(1);
	//exit(1);
	Pressed = true;
	Action();
	if (actData != NULL) {
		actData(Data);
	}
};

void ButtonControl::MouseUp(int b) {
	//exit(1);
	Pressed = false;
}
