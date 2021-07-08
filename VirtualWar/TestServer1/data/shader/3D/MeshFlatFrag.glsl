#version 330 core
uniform sampler2D tCol;
uniform vec3 mCol;
in vec3 oUv;
out vec4 color;

void main(){

    vec4 fc;
        vec2 uv;

    uv.x = oUv.x;
    uv.y = 1.0-oUv.y;
    vec3 cTex = texture(tCol,uv).rgb;

    fc.rgb = cTex*mCol;
    fc.a = 1.0;

    color = fc;

}