#include "pch.h"
#include "BoolControl.h"
#include "UI.h"

BoolControl::BoolControl() {

	White = new Texture2D("Edit/white1.png", true);

}

void BoolControl::Render() {

	UI::DrawTexture(White, GetX(), GetY(), GetW(), GetW(), 1, 1, 1, 1);
	if (State) {

		UI::DrawTexture(White, GetX() + 2, GetY()+2, GetW() - 4, GetH() - 4, 0.2f, 0.2f, 0.2f, 1.0f);

	}
	UI::RenderText(GetX() + 25, GetY() + 4, GetText(), 1, 1, 1, 1);
}

void BoolControl::MouseDown(int b) {

	if (State) {
		State = false;
	}
	else {
		State = true;
	}
	StateChange(State);
};