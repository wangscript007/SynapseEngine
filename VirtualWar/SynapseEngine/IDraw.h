#pragma once

#include <vector>
#include <list>
#include "kEffect.h"
class Texture2D;
class FXImageDraw;
class kEffect;





struct DrawInfo {

	float x[4];
	float y[4];
	float z;
	Texture2D* Tex;
	Texture2D* Norm;
	float r, g, b, a;

};

struct DrawList {

	std::vector<DrawInfo*> Draws;
	Texture2D* Tex;
	Texture2D* Norm;

};

class IDraw
{
public:
	IDraw(int w,int h);

	void Begin();

	DrawList* GetDrawList(Texture2D* tex);
	void DrawTexCoords(float* x, float* y, Texture2D* img, Texture2D* norm, float r, float g, float b, float a);
	void DrawTexCoords(float* x, float* y, Texture2D* img, float r, float g, float b, float a);
	void DrawTex(int x, int y, int w, int h,Texture2D * tex,float r, float g, float b, float a);
	void End();
	void End(bool leaveShader);
	void End(kEffect* fx,bool alpha,bool add=false);
	void EndNoBlend();
	void SingleDrawTex(int x, int y, int w, int h, Texture2D* tex, float r, float g, float b, float a);


private:

	std::vector<DrawList*> Draws;
	float drawZ;
	FXImageDraw* fx;
	int dw, dh;
	float* vdat = NULL;
	int* idat = NULL;
	GLuint va=0, vb=0, vc=0;
	bool madeGL = false;


};

