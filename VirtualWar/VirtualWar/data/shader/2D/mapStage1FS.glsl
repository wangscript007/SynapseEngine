#version 330 core

in vec4 UV;
in vec4 col;

uniform sampler2D tR;
uniform sampler2D tS;
uniform int sW,sH;

out vec4 color;

void main(){

      vec2 pp = gl_FragCoord.xy;

    if(pp.x<0 || pp.x>sW || pp.y <0 || pp.y>sH){

        discard;
        return;

    }

    vec3 texCol = texture(tS,UV.zw).rgb;

    float texAlpha = texture(tR,UV.xy).a;

    vec4 fcol;
    fcol.rgb = texCol;
    fcol.a = 1.0;

    color = fcol;

}