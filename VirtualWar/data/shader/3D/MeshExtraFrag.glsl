#version 330 core

uniform sampler2D tCol;
uniform sampler2D tNorm;
uniform samplerCube tShadow;
uniform sampler2D tSpec;

//uniform vec3 mCol;
in vec3 oUv;
out vec4 color;

void main(){

    vec4 fc = vec4(0,0,0,0);

    fc.r = texture(tSpec,oUv.xy).r;
    
    fc.a = 1.0;

    color = fc;

}