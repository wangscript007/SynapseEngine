#include "pch.h"
#include "MainMenuControl.h"
#include "UI.h"
#include "UITheme.h"

MainMenuControl::MainMenuControl() {

	Items.resize(0);
	iRight = new Texture2D("edit/iRight1.png", true, false);

};



MenuItem* MainMenuControl::AddItem(const char* text,Texture2D* icon) {

	MenuItem* item = new MenuItem;

	item->Text = text;
	item->Items.resize(0);
	item->Icon = icon;

	Items.push_back(item);

	return item;

}

void MainMenuControl::MM_Menu(MenuItem* item, int x, int y, int dx, int dy) {

	int mh = 0;
	int mw = 0;

	for (int i = 0; i < item->Items.size(); i++) {

		auto it = item->Items[i];
		if (it->Seperator) {
			mh = mh + 8;
		}
		else {
			mh = mh + UI::TextHeight(it->Text) + 8;
			if (UI::TextWidth(it->Text) > mw)
			{
				mw = UI::TextWidth(it->Text);
			}
		}
	}

	dy = dy + 4;

	for (int i = 0; i < item->Items.size(); i++) {

		auto it = item->Items[i];
		//UI:::RenderText(dx, dy, it->Text, 1, 1, 1, 1);
		if (it->Seperator) {

			dy = dy + 8;

		}
		else {

			if (x >= dx && x <= (dx + mw+150))
			{
				if (y >= dy && y <= (dy + UI::TextHeight(it->Text))+4) {
					//	exit(1);
					OverItem = it;
					return;
				}
			}
		}
		if (it->Open) {

			MM_Menu(it, x, y, dx + mw+150, dy-3);

		}

		if (it->Seperator == false) {
			dy = dy + UI::TextHeight(it->Text) + 8;
		}
	}




}

void MainMenuControl::MouseMove(int x, int y, int mx, int my) {
	int rx = 3;
	OverItem = NULL;
	ActiveItem = NULL;
	for (int i = 0; i < Items.size(); i++) {

		auto mi = Items[i];

		if (x > rx-10 && x <= (rx + UI::TextWidth(mi->Text)))
		{
			if (y >= 0 && y <= (25)) {
				ActiveItem = mi;
			}
		}

		if (mi->Items.size() > 0) {

			if (mi->Open) {
				MM_Menu(mi, GetX() + x, y, GetX() + rx, GetY() + 25);
			}
		}
		rx = rx + UI::TextWidth(mi->Text) + 25;
	}

};

void MainMenuControl::DrawMenu(MenuItem* item, int dx, int dy) {

	int mh = 0;
	int mw = 0;

	for (int i = 0; i < item->Items.size(); i++) {

		auto it = item->Items[i];
		if (it->Seperator == false) {
			mh = mh + UI::TextHeight(it->Text) + 8;
			if (UI::TextWidth(it->Text) > mw)
			{
				mw = UI::TextWidth(it->Text);
			}
		}
		else {
			mh = mh + 8;
		}
	}

	mw = mw + 150;

	UI::Theme->DrawFrame(dx, dy, mw + 8, mh + 5, 1, 1, 1, 1);
	UI::Theme->DrawFrame(dx+1, dy+1, mw+6, mh+3, 0.3f, 0.3f, 0.3f, 1);
	dy = dy + 4;

	for (int i = 0; i < item->Items.size(); i++) {

		auto it = item->Items[i];
		if (it->Seperator) {

			UI::Theme->DrawFrame(dx, dy - 3, mw, 2, 0.7f, 0.7f, 0.7f, 1);
			dy = dy + 8;
		}
		else {
			if (OverItem == it) {

				UI::Theme->DrawFrame(dx, dy - 3, mw + 4, 23, 0.9f, 0.9f, 0.9f, 0.7f);

			};
			if (it->Icon != NULL) {
				UI::Theme->DrawImg(dx + 10, dy, 16, 16, it->Icon, 1, 1, 1, 1);
			}
			UI::RenderText(dx + 35, dy, it->Text, 1, 1, 1, 1);

			if (it->Items.size() > 0) {
				UI::DrawTexture(iRight, dx + mw - 12, dy+2, 12, 12, 1, 1, 1, 1);
			}
			//if (OverItem == it) {



			if (it->Open) {

				if (it->Items.size() > 0) {
					DrawMenu(it, dx + mw + 8 + 1, dy - 3);
				}

			}

			//		}
			dy = dy + UI::TextHeight(it->Text) + 8;
		}
	}


}; 

bool MainMenuControl::CheckMenuBounds(MenuItem * item,int dx, int dy,int mx,int my) {


	int mh = 0;
	int mw = 0;

	for (int i = 0; i < item->Items.size(); i++) {

		auto it = item->Items[i];
		if (it->Seperator) {
			mh = mh + 8;
		}
		else {
			mh = mh + UI::TextHeight(it->Text) + 8;
			if (UI::TextWidth(it->Text) > mw)
			{
				mw = UI::TextWidth(it->Text);
			}
		}
	}

	if (mx >= (dx-10) && mx <= (dx + mw + 8 +150))
	{
		if (my >= (dy) && my <= (dy + mh + 5))
		{
			return true;
		}
	}

	for (int i = 0; i < item->Items.size(); i++) {

		auto it = item->Items[i];
		//if (OverItem == it)
		//{
			if (it->Open) {
				if (CheckMenuBounds(it, dx + mw + 8+150, dy, mx, my))
				{
					return true;
				}
			}

	//	}
		dy = dy + UI::TextHeight(it->Text) + 8;
	}

	return false;
	//UI::Theme->DrawFrame(dx, dy, mw + 8, mh + 5, 0.5f, 0.5f, 0.5f, 0.7f);

}

bool MainMenuControl::InBounds(int x, int y) {

	int mx = 3;
//	return false;

	//printf(">>>X:%d Y:%d\n", x, y);

	for (int i = 0; i < Items.size(); i++) {

		auto mi = Items[i];

		if (x >= LocalX() + mx-15 && x <= (LocalX() + mx + UI::TextWidth(mi->Text)))
		{
			if (y >= LocalY() && y <= LocalY()+GetH()) {
				return true;
			}

		}



	//	UI:::RenderText(GetX() + mx, GetY() + 3, mi->Text, 1, 1, 1, 1);

	//	UI::Theme->DrawFrame(GetX() + mx + UI::TextWidth(mi->Text) + 5, GetY(), 2, GetH(), 1, 1, 1, 1);


		if (mi->Open) {
			if (mi->Items.size() > 0) {

				if (CheckMenuBounds(mi, LocalX() + mx, LocalY() + 25, x, y)) {
					return true;
				}


			}
		}
		mx = mx + UI::TextWidth(mi->Text) + 25;

	}

	return false;

};

void MainMenuControl::MouseDown(int b) {

	if (b != 0) return;

	if (OverItem != NULL) {


			OverItem->Action();
			OverItem->Action2(OverItem);



		if (OverItem->act == NULL) {
			if (OverItem->Open == false) {
				OverItem->Open = true;
			}
			else {
				OverItem->Open = false;
			}
		}
		return;

	}

	if (ActiveItem != NULL) {


		if (ActiveItem->Open == false) {
			ActiveItem->Open = true;
		}
		else {
			ActiveItem->Open = false;
		}

	}

}

void MainMenuControl::Render() {

	UI::Theme->DrawFrame(0, GetY(), GetW(), GetH(), 0.4f, 0.4f, 0.4f, 1);

	int mx = 3;

	for (int i = 0; i < Items.size(); i++) {

		auto mi = Items[i];

		if (ActiveItem == mi) {

			UI::Theme->DrawFrame(GetX() + mx-10, GetY() + 5, UI::TextWidth(mi->Text) + 23, 15, 0.9f, 0.9f, 0.9f, 0.7f);

		}

		UI::RenderText(GetX()+mx, GetY() + 5, mi->Text, 1, 1, 1, 1);

	//	UI::Theme->DrawFrame(GetX()+mx + UI::TextWidth(mi->Text) + 5, GetY(), 2, GetH(), 1, 1, 1, 1);


		if (mi->Items.size() > 0) {

			if (mi->Open) {

				DrawMenu(mi, GetX() + mx, GetY() + 25);
			}
		}


		mx = mx + UI::TextWidth(mi->Text) + 25;
	}

}

void MainMenuControl::Update() {


};