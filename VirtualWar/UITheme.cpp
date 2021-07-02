#include "pch.h"
#include "UITheme.h"
#include "UI.h"

void UITheme::DrawDyanmicBox(int x, int y, int w, int h, Texture2D* t, Texture2D* d, Texture2D* l, Texture2D* r, Texture2D* lt, Texture2D* ld, Texture2D* rt, Texture2D* rd, Texture2D* mid, float cr, float cg, float cb, float ca)
{

	UI::DrawTexture(lt, x, y, 8, 8, cr,cg,cb,ca);
	UI::DrawTexture(ld, x, y + h - 8, 8, 8, cr, cg, cb, ca);
	UI::DrawTexture(rt, x + w - 8, y, 8, 8, cr, cg, cb, ca);
	UI::DrawTexture(rd, x + w - 8, y + h - 8, 8, 8, cr, cg, cb, ca);
	UI::DrawTexture(l, x, y + 8, 8, h - 16, cr, cg, cb, ca);
	UI::DrawTexture(r, x + w - 8, y + 8, 8, h - 16, cr, cg, cb, ca);
	UI::DrawTexture(t, x + 8, y, w - 16, 8, cr, cg, cb, ca);
	UI::DrawTexture(d, x + 8, y + h - 8, w - 16, 8, cr, cg, cb, ca);
	UI::DrawTexture(mid, x + 8, y + 8, w - 16, h - 16,cr,cg,cb,ca);

}
