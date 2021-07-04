#pragma once
#include "Texture2D.h"
class UIDragObject
{
public:
	UIDragObject(void * data) {

		x = 0;
		y = 0;
		Icon = NULL;
		Text = "";
		Data = data;

	}

	int x, y;
	Texture2D* Icon;
	const char* Text;
	const char* Path;
	void* Data;
	int ID1, ID2, ID3, ID4;


};

