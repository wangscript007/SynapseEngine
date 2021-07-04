#include "kPostProcess.h"
#include "VirtualWarApp.h"
kPostProcess::kPostProcess() {

	drawer = new IDraw(VirtualWarApp::rWidth, VirtualWarApp::rHeight);

}

void kPostProcess::DrawImage(int x, int y, int w, int h, float r, float g, float b, float a, Texture2D* img) {

	drawer->Begin();

	drawer->DrawTex(x, y, w, h, img, r, g, b, a);

	drawer->End(true);

}