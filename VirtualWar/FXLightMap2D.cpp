#include "pch.h"
#include "FXLightMap2D.h"
#include "Application.h"
#include "TMaths.h"
FXLightMap2D::FXLightMap2D(int w, int h) {

	load("Shader/2D/drawLightMapVS.glsl", "Shader/2D/drawLightMapFS.glsl");
	pw = w;

	ph = h;
	//while(true){}
	vMat = glm::mat4(1.0f);

	vMat = glm::translate(vMat, glm::vec3(100, 0, 0));

}

void FXLightMap2D::SetLight(MapLight* l)
{

	light = l;

}

void FXLightMap2D::setPars() {

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
		p13 = glGetUniformLocation(pID, (GLchar*)"view");

	}

	vMat = glm::mat4(1.0f);

	float cz = camZ - 1.0f;

	float ca = TMaths::DegToRad(mapRot);

	if (uVmat) {
		vMat = glm::translate(vMat, glm::vec3(pw / 2, ph / 2, 0));
		vMat = glm::rotate(vMat, ca, glm::vec3(0, 0, 1));
		vMat = glm::translate(vMat, glm::vec3(-CamX, -CamY, 0));
	}
	//	cMat = glm::mat4(1.0f);
	//	cMat = glm::translate(cMat,glm)







	auto lp = light->GetRPos();
	auto ld = light->GetDiffuse();
	auto lr = light->GetRRange();



	glUniform1i(p1, 0);
	glUniform1i(p2, 1);
	glUniform1i(p3, 2);

	glUniformMatrix4fv(p4, 1, false, glm::value_ptr(pMat));
	glUniformMatrix4fv(p13, 1, false, glm::value_ptr(vMat));
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


	float da = light->GetSpotDir();// -mapRot;


	da = mapRot + light->GetSpotDir();// -light->GetSpotDir();
	for (int i = 0; i < 8; i++) {
		if (da > 360.0) {
			da = da - 360.0f;
		}
		if (da < 0.0) {
			da = 360 + da;
		}
	}


	glUniform1i(p8, si);
	glUniform1f(p9, light->GetSpotAngle());
	glUniform1f(p10, da);
	glUniform1f(p11, pw);
	glUniform1f(p12, ph);


	//setInt("tR", 0);
	//setInt("tN", 1);
	//setInt("tS", 2);

	auto sm = light->GetBakedShadows();
	sm->Bind(2);

	//ShadowMap->Bind(2);






};