#include "pch.h"
#include "FXShadow2D.h"

FXShadow2D::FXShadow2D(int w, int h) {

	load("Shader/2D/drawShadowVS.glsl", "Shader/2D/drawShadowFS.glsl");
	pw = w;
	ph = h;
	//while(true){}



}

void FXShadow2D::SetLight(MapLight* l)
{

	light = l;

}

void FXShadow2D::setPars() {

	pw = Application::RenW;
	ph = Application::RenH;
	glm::mat4 pMat = glm::ortho((float)0, (float)pw, (float)ph, (float)0, (float)-100, (float)100);


	if (!gotPars) {
		gotPars = true;

		p1 = glGetUniformLocation(pID, (GLchar*)"tR");
	
		p2 = glGetUniformLocation(pID, (GLchar*)"proj");
		p3 = glGetUniformLocation(pID, (GLchar*)"lightPos");
		p4 = glGetUniformLocation(pID, (GLchar*)"lightRange");

		p5 = glGetUniformLocation(pID, (GLchar*)"sW");
		p6 = glGetUniformLocation(pID, (GLchar*)"sH");

	}
	auto lp = light->GetRPos();
	auto ld = light->GetDiffuse();
	auto lr = light->GetRRange();
	glUniform1i(p1, 0);

	glUniformMatrix4fv(p2, 1, false, glm::value_ptr(pMat));
	glUniform3f(p3, lp.X, lp.Y, lp.Z);
	glUniform1f(p4,lr);
	glUniform1f(p5, pw);
	glUniform1f(p6, ph);




};

