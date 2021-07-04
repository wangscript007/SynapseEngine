#version 330 core

in vec2 UV;
in vec4 col;

uniform sampler2D tR;
uniform sampler2D tS;
uniform int sW,sH;
uniform vec3 lightPos;
uniform vec3 lightDiff;
uniform int noLight;
uniform float lightRange;
uniform int noShadows;

out vec4 color;

float calcLight(vec2 lpos,vec2 ppos,float range)
{

    float xd,yd;
    xd = lpos.x-ppos.x;
    yd = lpos.y-ppos.y;
    float mag = sqrt(xd*xd+yd*yd);
    mag = mag / range;

    if(mag>1.0) mag = 1.0;
    mag = 1.0 - mag;
    return mag; 


}

void main(){

  vec2 pp = gl_FragCoord.xy;

    if(pp.x<0 || pp.x>sW || pp.y <0 || pp.y>sH){

        discard;
        return;

    }

    vec3 texCol = texture(tR,UV).rgb;
    

    vec2 suv;

    suv.x = gl_FragCoord.x / sW;
    suv.y = gl_FragCoord.y / sH;

    vec2 pixPos = gl_FragCoord.xy;

    pixPos.y = sH - pixPos.y;

    //suv.y = 1.0-suv.y;

    if(noShadows==0){
    float shadow = texture(tS,suv).r;

    texCol = texCol * vec3(shadow,shadow,shadow);

    }
    //texCol.rgb = vec3(shadow,shadow,shadow);
    float lv = calcLight(lightPos.xy,pixPos.xy,lightRange);

   

    float texAlpha = texture(tR,UV.xy).a;

    vec4 fcol;
    fcol.rgb = texCol * vec3(lv,lv,lv) * lightDiff;
    fcol.a = texAlpha;

    color = fcol;

}