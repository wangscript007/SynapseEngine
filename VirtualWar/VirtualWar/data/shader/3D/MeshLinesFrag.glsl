#version 330 core

uniform vec3 lineCol;

out vec4 color;

void main(){

    vec4 fc;
    fc.rgb = lineCol;
    fc.a = 1.0;

    color = fc;

}