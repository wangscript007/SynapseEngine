#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vPos;

uniform mat4 mProj;
uniform mat4 mView;


void main(){


    gl_Position = mProj * mView * vec4(vPos,1.0);

}