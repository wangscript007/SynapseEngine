#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vUv;
layout(location = 2) in vec3 vCol;
layout(location = 3) in vec3 vExt; 

uniform mat4 mProj;
uniform mat4 mModel;
uniform mat4 mView;

out vec3 oUv;
out vec3 oCol;
out vec3 oExt;

void main(){
 
   oUv = vUv;
   oCol = vCol;
    oExt = vExt;

    gl_Position = mProj * mView *mModel* vec4(vPos,1.0);



}