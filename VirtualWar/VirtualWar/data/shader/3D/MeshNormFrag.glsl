#version 330 core


in vec3 fVert;
in vec3 fNorm;

// Ouput data
out vec4 color;

void main(){
 
 

    color = vec4(fNorm,1.0);
}