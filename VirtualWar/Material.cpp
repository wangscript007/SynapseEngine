#include "pch.h"
#include "Material.h"

Material::Material() {

	if (White == NULL) {

		White = new Texture2D("edit/tex2/white1.png", false);
		NormalBlank = new Texture2D("edit/tex2/nm1.png", false);
		Black = new Texture2D("edit/tex2/black.png", false);
	}
	ColorTex = White;
	NormalTex = NormalBlank;
	SpecularTex = Black;

}

void Material::SetColorTex(Texture2D* tex) {

	ColorTex = tex;

}

void Material::SetNormalTex(Texture2D* tex) {

	NormalTex = tex;

}

void Material::SetSpecularTex(Texture2D* tex) {

	SpecularTex = tex;

}

Texture2D* Material::GetColorTex() {

	return ColorTex;

}

Texture2D* Material::GetNormalTex() {

	return NormalTex;

}

Texture2D* Material::GetSpecularTex() {

	return SpecularTex;

}

void Material::Bind() {

	ColorTex->Bind(0);
	if (NormalTex != NULL) {
		NormalTex->Bind(1);
	}
	if (SpecularTex != NULL) {
		SpecularTex->Bind(3);
	}

}

void Material::Release() {

	ColorTex->Release(0);
	if (NormalTex != NULL) {
		NormalTex->Release(1);
	}
	if (SpecularTex != NULL) {
		SpecularTex->Release(3);
	}

}

Texture2D* Material::White = NULL;
Texture2D* Material::NormalBlank = NULL;
Texture2D* Material::Black = NULL;