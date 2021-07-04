#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec4 vCol;
layout(location = 2) in vec3 vUv;
layout(location = 3) in vec3 vNorm;
layout(location = 4) in vec3 vBiNorm;
layout(location = 5) in vec3 vTan;

uniform mat4 mProj;
uniform mat4 mModel;
uniform mat4 mView;


out vec3 fVert;
out vec3 fNorm;

void main(){

	
       mat4 tMat = mView * mModel;

     vec3 fP = vec3(tMat * vec4(vPos,1.0));

    fVert = fP;




	gl_Position = mProj * mView *mModel* vec4(vPos,1.0);


	
}

