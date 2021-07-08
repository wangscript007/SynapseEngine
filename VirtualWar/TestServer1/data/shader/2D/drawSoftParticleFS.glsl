#version 330 core

in vec2 UV;
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
uniform float pAlpha;

float dot2(vec2 a,vec2 b){

    return a.x*b.x+a.y*b.y;

}

float degToRad(float v){

 return ( v * 180.0 ) / 3.141592653589793238463 ;


}

void main(){

    vec3 texCol = texture(tR,UV).rgb;

    float texAlpha = texture(tR,UV).a * col.a;

    if(texAlpha<0.01)
    {
        discard;
        return;
    }

    vec2 pixPos = gl_FragCoord.xy;
    vec2 lPos = lightPos.xy;

    if(pixPos.x>sW || pixPos.y>sH){

        discard;
        return;

    }

    if(pixPos.x<0 || pixPos.y<0){
        discard;
        return;
    }

    pixPos.x = pixPos.x / sW;
    pixPos.y = (sH-pixPos.y) / sH;

    lPos.x = lPos.x / sW;
    lPos.y = lPos.y / sH;

    vec3 L = vec3(lPos.x-pixPos.x,lPos.y-pixPos.y,1.0);


    L = normalize(L);

    vec3 texNorm = texture(tN,UV).rgb;

    texNorm.xy = -2.0+texNorm.xy*2.0;

    vec3 N = vec3(texNorm.x,texNorm.y,1.0+(lightPos.z-1.0));

    float dp = dot(L,N);

    //--- Range

    float xd = (lPos.x*sW)-(pixPos.x*sW);
    float yd = (lPos.y*sH)-(pixPos.y*sH);
    float mag = sqrt(xd*xd+yd*yd);
    mag = mag / lightRange;

    if(mag>1.0) mag = 1.0;
    if(mag<0) mag = 0.0;
    mag = 1.0-mag;


   
    vec3 pc = vec3(dp,dp,dp);

    pc.r = pc.r * mag;
    pc.g = pc.g * mag;
    pc.b = pc.b * mag;

    /// ---- Shadow

    vec2 nv = pixPos.xy;

    nv.y = 1.0-nv.y;

    float fs = 0.0;
    float fn = 0;

    float dec = 0.002;

    for(float x=-4;x<5;x++){
        for(float y=-4;y<5;y++){
            
            vec2 av;

            av.x = nv.x+(x*dec);
            av.y = nv.y+(y*dec);

            fs = fs + texture(tS,av).r;

            fn=fn+1;

        }
    }

    fs = fs / fn;

    //fs = 1.0;
 //fs = 1.0;


    pc = pc * fs;

    vec4 fCol;
    

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

        pc.rgb = pc.rgb * vec3(fv,fv,fv);



      




    }
    

    fCol.rgb = texCol * pc * lightDiff * col.rgb;
    //fCol.rgb = texCol * pc;
    fCol.rgb = vec3(20,20,20)*texCol;





    fCol.a = texAlpha * col.a;


    color = fCol;

}
