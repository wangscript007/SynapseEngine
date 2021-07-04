#include "VirtualWarApp.h"
#include "FXTextDraw.h"

FXTextDraw::FXTextDraw(int w, int h) {

	load("data/Shader/2D/drawVSText.glsl", "data/Shader/2D/drawFSText.glsl");
	pw = w;
	ph = h;
};

void FXTextDraw::setPars() {

	pw = VirtualWarApp::rWidth;
	ph = VirtualWarApp::rHeight;
	glm::mat4 pMat = glm::ortho((float)0, (float)pw, (float)ph, (float)0, (float)-100, (float)100);
	if (gotPars == NULL) {
		p1 = glGetUniformLocation(pID, (GLchar*)"tR");
		p2 = glGetUniformLocation(pID, (GLchar*)"proj");
		gotPars = true;
	}

	glUniform1i(p1, 0);

	//setInt("tR", 0);

	glUniformMatrix4fv(p2, 1, false, glm::value_ptr(pMat));
	//setMat("proj", pMat);


};