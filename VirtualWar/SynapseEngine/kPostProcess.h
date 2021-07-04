#pragma once
#include "kEffect.h"
#include "Texture2D.h"
#include "IDraw.h"
class kPostProcess
{
public:

	kPostProcess();

	//void setGame(kamGame* g);

	//kamGame* getGame();

	virtual Texture2D* process(Texture2D* base) { return NULL; };
	void DrawImage(int x, int y, int w, int h, float r, float g, float b, float a, Texture2D* img);

protected:

	IDraw* drawer;

	//kamGame* game;


};

