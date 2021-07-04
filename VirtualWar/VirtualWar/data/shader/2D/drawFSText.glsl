#version 330 core

in vec2 UV;
in vec4 col;

out vec4 color;

uniform sampler2D tR;


void main(){

    vec4 co = texture(tR,UV) * col;

if(co.r==0.0)
{

    discard;
    return;
}

   co.g = co.r;
   co.b = co.r;

    //co.rgb = vec3(1,1,1);

    color = co;

}