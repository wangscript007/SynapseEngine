#pragma once
#include "Texture2D.h"
#include "UI.h"
class Texture2D;

class UITheme
{
public:

	virtual void DrawButton(int x, int y, int w, int h, const char* text,bool over,bool pressed) {};
	virtual void DrawFrame(int x, int y, int w, int h, float r, float g, float b, float a) {};
	virtual void DrawImg(int x, int y, int w, int h, Texture2D* tex, float r, float g, float b, float a)
	{
		UI::DrawTexture(tex, x, y, w, h, r, g, b, a);
	}

	void DrawDyanmicBox(int x, int y, int w, int h, Texture2D* t, Texture2D* d, Texture2D* l, Texture2D* r, Texture2D* lt, Texture2D* ld, Texture2D* rt, Texture2D* rd, Texture2D* mid,float cr,float cg,float cb,float ca);

	Texture2D* ButMid;
	Texture2D* ButTop;
	Texture2D* ButDown;
	Texture2D* ButLeft;
	Texture2D* ButRight;
	Texture2D* ButLeftTop;
	Texture2D* ButLeftDown;
	Texture2D* ButRightTop;
	Texture2D* ButRightDown;

	Texture2D* FrameBG;

};

