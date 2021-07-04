#include "pch.h"
#include "FXSoftParticle2D.h"

FXSoftParticle2D::FXSoftParticle2D(int w, int h) {

	load("Shader/2D/drawSoftParticleVS.glsl", "Shader/2D/drawSoftParticleFS.glsl");
	pw = w;
	ph = h;

}


void FXSoftParticle2D::SetLight(MapLight* l)
{

	light = l;

}

void FXSoftParticle2D::setPars() {

	pw = Application::RenW;
	ph = Application::RenH;
	glm::mat4 pMat = glm::ortho((float)0, (float)pw, (float)ph, (float)0, (float)-100, (float)100);



	if (!gotPars) {
		gotPars = true;

		p1 = glGetUniformLocation(pID, (GLchar*)"tR");
		p2 = glGetUniformLocation(pID, (GLchar*)"tN");
		p3 = glGetUniformLocation(pID, (GLchar*)"tS");
		p4 = glGetUniformLocation(pID, (GLchar*)"proj");
		p5 = glGetUniformLocation(pID, (GLchar*)"lightPos");
		p6 = glGetUniformLocation(pID, (GLchar*)"lightDiff");
		p7 = glGetUniformLocation(pID, (GLchar*)"lightRange");
		p8 = glGetUniformLocation(pID, (GLchar*)"lightSpot");
		p9 = glGetUniformLocation(pID, (GLchar*)"lightSpotAngle");
		p10 = glGetUniformLocation(pID, (GLchar*)"lightDir");
		p11 = glGetUniformLocation(pID, (GLchar*)"sW");
		p12 = glGetUniformLocation(pID, (GLchar*)"sH");

	}
	auto lp = light->GetRPos();
	auto ld = light->GetDiffuse();
	auto lr = light->GetRRange();
	glUniform1i(p1, 0);
	glUniform1i(p2, 1);
	glUniform1i(p3, 2);
	ShadowMap->Bind(2);
	glUniformMatrix4fv(p4, 1, false, glm::value_ptr(pMat));
	glUniform3f(p5, lp.X, lp.Y, lp.Z);
	glUniform3f(p6, ld.X, ld.Y, ld.Z);
	glUniform1f(p7, lr);

	int si = 0;

	if (light->GetSpot()) {

		si = 1;

	}
	else {
		si = 0;
	}


	float da = light->GetSpotDir() + mapRot;
	if (da > 360.0) {
		da = da - 360.0f;
	}
	if (da < 0.0) {
		da = 360 + da;
	}

	glUniform1i(p8, si);
	glUniform1f(p9, light->GetSpotAngle());
	glUniform1f(p10, da);
	glUniform1f(p11, pw);
	glUniform1f(p12, ph);



};