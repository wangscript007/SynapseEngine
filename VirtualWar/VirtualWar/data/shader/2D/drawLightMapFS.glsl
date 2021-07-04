#version 330 core

in vec4 UV;
in vec4 col;

out vec4 color;

uniform int lightSpot;
uniform float lightSpotAngle;
uniform float lightDir;
uniform sampler2D tLM;
uniform sampler2D tR;
uniform sampler2D tS;
uniform sampler2D tN;
uniform vec3 lightPos;
uniform vec3 lightDiff;
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

    vec3 texCol = texture(tR,UV.xy).rgb;

    float texAlpha = texture(tR,UV.xy).a;

    vec3 suv;

    suv.x = UV.b;
    suv.y = UV.a;
    suv.z = 0;
 
    vec3 sCol = texture(tS,suv.xy).rgb;

   vec2 pixPos = gl_FragCoord.xy;
    vec2 lPos = lightPos.xy;

    pixPos.x = pixPos.x / sW;
    pixPos.y = (sH-pixPos.y) / sH;

    lPos.x = lPos.x / sW;
    lPos.y = lPos.y / sH;


    float xd = (lPos.x*sW)-(pixPos.x*sW);
    float yd = (lPos.y*sH)-(pixPos.y*sH);
    
    float mag = sqrt(xd*xd+yd*yd);
    mag = mag / lightRange;

    if(mag>1.0) mag = 1.0;
    if(mag<0) mag = 0.0;
    mag = 1.0-mag;

    
    if(lightSpot==1){

         xd = (lightPos.x)-(pixPos.x*sW);
        yd = (lightPos.y)-(pixPos.y*sH);


        float la = atan(yd,xd);

        float ds = la * (180.0/3.141592653589793238463);
        
        if(ds<0.0)
        {
            ds = 360.0+ds;
        }
        if(ds>360.0){
            ds = ds - 360.0;
        }

        float a1 = max(lightDir,ds)-min(lightDir,ds);
        float a2 = min(lightDir,ds)+(360.0-max(lightDir,ds));

        float fv = 0.0;

        if(a1<a2){

            fv = a1;
            
        }else{

            fv = a2;

        }

        if(fv<0){
            fv=-fv;
        }

        fv = fv / lightSpotAngle;

      
        fv = 1.0-fv;

        //pc.rgb = pc.rgb * vec3(fv,fv,fv);

        mag = mag * fv;


      




    }



   // suv.x = 1.0-UV.z;
  //  suv.y = UV.w;


//    float sv = texture(tS,suv).r;
    texCol.rgb = texCol.rgb * vec3(mag,mag,mag) * lightDiff;

    vec4 fcol;
    fcol.rgb = texCol *sCol;//texCol * vec3(sv,sv,sv);
    fcol.a = 1.0;

    color = fcol;

}
