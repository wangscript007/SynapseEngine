#include "pch.h"
#include "ImageControl.h"
#include "Texture2D.h"
#include "UI.h"
ImageControl::ImageControl(Texture2D* image) {

	Image = image;
	cR = cG = cB = cA = 1.0f;

};


ImageControl::ImageControl(const char* path,bool alpha) {


	Image = new Texture2D(path, alpha);
	cR = cG = cB = cA = 1.0f;

};

void ImageControl::Render() {

	UI::DrawTexture(Image, GetX(), GetY(), GetW(), GetH(),cR,cG,cB,cA);

};