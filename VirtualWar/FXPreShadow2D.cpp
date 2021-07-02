#include "pch.h"
#include "FXPreShadow2D.h"
#include "TMaths.h"
FXPreShadow2D::FXPreShadow2D(int w,int h) {
	
	//FXLight2D::FXLight2D(int w, int h) {

		load("Shader/2D/drawpshadowVS.glsl", "Shader/2D/drawpshadowFS.glsl");
		//pw = w;
	//	ph = h;
		sW = w;
		sH = h;
		//while(true){}



	

}

void FXPreShadow2D::setPars() {


	int pw = Application::RenW;
	int ph = Application::RenH;
	glm::mat4 pMat = glm::ortho((float)0, (float)pw, (float)ph, (float)0, (float)-100, (float)100);


	if (!gotPars) {
		gotPars = true;

		p1 = glGetUniformLocation(pID, (GLchar*)"tR");
		p2 = glGetUniformLocation(pID, (GLchar*)"proj");
		p3= glGetUniformLocation(pID, (GLchar*)"sW");
		p4 = glGetUniformLocation(pID, (GLchar*)"sH");
		p5 = glGetUniformLocation(pID, (GLchar*)"view");

	}

	glUniform1i(p1, 0);
	glUniformMatrix4fv(p2,1, false, glm::value_ptr(pMat));
	glUniform1f(p3,pw);
	glUniform1f(p4, ph);

	vMat = glm::mat4(1.0f);

	float cz = 1.0f - 1.0f;

	float ca = TMaths::DegToRad(mapRot);

	vMat = glm::translate(vMat, glm::vec3(pw / 2, ph / 2, 0));
	vMat = glm::rotate(vMat, ca, glm::vec3(0, 0, 1));
	vMat = glm::translate(vMat, glm::vec3(-CamX, -CamY, 0));
	glUniformMatrix4fv(p5, 1, false, glm::value_ptr(vMat));

		//setInt("tR", 0);
		//setMat("proj", pMat);
	//	setFloat("sW", pw);
//		setFloat("sH", ph);

};