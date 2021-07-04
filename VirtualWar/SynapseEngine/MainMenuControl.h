#pragma once
#include "UIControl.h"
#include <vector>
#include <functional>
#include "Texture2D.h"

struct MenuItem {

	std::function<void()> act = NULL;
	const char* Text;
	std::vector<MenuItem*> Items;
	Texture2D* Icon;
	void* Data;
	int DataInt;
	std::function<void(MenuItem* item)> act2 = NULL;
	bool Seperator = false;
	void Action2(MenuItem* item) {

		if (act2 != NULL) {
			act2(item);
		}

	}

	void Action(){

		if (act != NULL) {
			act();
		}
	

	}
	void SetAction(std::function<void()> action)
	{
		act = action;
	}
	MenuItem * AddItem(const char* text,Texture2D* icon = NULL) {

		MenuItem* item = new MenuItem;

		item->Icon = icon;
		item->Text = text;
		item->Items.resize(0);

		Items.push_back(item);

		return item;

	};

	void AddSeperator()
	{

		MenuItem* item = new MenuItem;

		//item->Text = text;

		item->Seperator = true;
		item->Items.resize(0);

		Items.push_back(item);


		//return item;

	}

	bool Open = false;

};

class MainMenuControl :
	public UIControl
{
public:

	MainMenuControl();

	MenuItem * AddItem(const char* text,Texture2D* icon = NULL);


	void MouseMove(int x, int y, int mx, int my);
	void MouseDown(int b);

	void DrawMenu(MenuItem* item, int dx, int dy);
	bool CheckMenuBounds(MenuItem* item, int dx, int dy,int mx,int my);
	void MM_Menu(MenuItem* item, int x, int y, int dx, int dy);
	bool InBounds(int mx, int my);

	void Update();
	void Render();


private:
	std::vector<MenuItem*> Items;
	MenuItem* OverItem = NULL;
	Texture2D* iRight;
	MenuItem* ActiveItem = NULL;
};



