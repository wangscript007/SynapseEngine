#version 330 core

in vec2 UV;
in vec4 col;

out vec4 color;

uniform sampler2D fb;
uniform sampler2D blur;



void main()
{

    vec2 uv = UV;
    uv.y = 1.0-uv.y;

    vec3 fc = texture2D(fb,uv).rgb;
    vec3 bv = texture2D(blur,uv).rgb;

    fc = fc + bv;     
    // color = vec4(bv.r,bv.g,bv.b,1.0);

    color = vec4(fc.r,fc.g,fc.b,1.0);

}