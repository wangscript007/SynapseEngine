#version 330 core

in vec2 UV;
in vec4 col;

out vec4 color;



uniform sampler2D tR;

uniform vec3 lightPos;

uniform float lightRange;
uniform float sW;
uniform float sH;

float dot2(vec2 a,vec2 b){

    return a.x*b.x+a.y*b.y;

}

float degToRad(float v){

 return ( v * 180.0 ) / 3.141592653589793238463 ;


}

void main(){

 

    vec2 pixPos = gl_FragCoord.xy;
    vec2 lPos = lightPos.xy;

    pixPos.x = pixPos.x / sW;
    pixPos.y = (sH-pixPos.y) / sH;

    lPos.x = lPos.x / sW;
    lPos.y = lPos.y / sH;



    /// ---- Shadow

    float steps = 64;

    float xd,yd;

    xd = (lightPos.x)-(pixPos.x*sW);
    yd = (lightPos.y)-(pixPos.y*sH);

    xd = xd / steps;
    yd = yd / steps;
    
    float lx,ly;

    lx = pixPos.x*sW;
    ly = pixPos.y*sH;

    float sv = texture(tR,vec2(lx/sW,1.0-(ly/sH))).r;

    if(sv==0.0){

        color = vec4(1,1,1,1);
        return;

    }

    float fs = 0.0;
    for(int i=0;i<steps;i++){


        lx = lx + xd;
        ly = ly + yd;

        if(lx>0 && ly>0 && lx<sW && ly<sH)
        {

        float tv = texture(tR,vec2(lx/sW,1.0-(ly/sH))).r;

        if(tv<0.1)
        {
//            fs=1.0f;
            discard;
            return;
            fs=1;
            break;
        }
        }

    }

  
    
//   fs = fs / steps;



    fs = 1.0-fs;

    if(fs<0) fs = 0;
    
    


    vec4 fc = vec4(fs,fs,fs,1.0);


    fc.rgb = fc.rgb;
    fc.a = 1.0;

    color = fc;

}
