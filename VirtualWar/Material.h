#pragma once
#include "Texture2D.h"
class Material
{
public:

	Material();

	void SetColorTex(Texture2D* tex);
	void SetNormalTex(Texture2D* tex);
	void SetSpecularTex(Texture2D* tex);

	Texture2D* GetColorTex();
	Texture2D* GetNormalTex();
	Texture2D* GetSpecularTex();

	void Bind();
	void Release();

private:
	Texture2D* ColorTex;
	Texture2D* NormalTex;
	Texture2D* SpecularTex;
	static Texture2D* White;
	static Texture2D* NormalBlank;
	static Texture2D* Black;

};

