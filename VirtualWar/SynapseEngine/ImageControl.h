#pragma once
#include "UIControl.h"

class Texture2D;

class ImageControl : public UIControl
{
public:

	ImageControl() {};
	ImageControl(Texture2D* img);
	ImageControl(const char* path,bool alpha);
	void SetColor(float r, float g, float b, float a) {
		cR = r;
		cG = g;
		cB = b;
		cA = a;
	}
	void Render();


protected:

	Texture2D* Image;
	float cR, cG, cB, cA;

};

