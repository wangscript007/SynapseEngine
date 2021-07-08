#version 330 core

in vec2 UV;
in vec4 col;

out vec4 color;



uniform sampler2D tR;




uniform float sW;
uniform float sH;



void main(){

    float alpha = texture(tR,UV).a;

    float sc = 1.0;

    if(alpha>0.2)
    {
      
        sc=0;

    //       sc = 1.0;

    }else{
        discard;
        return;
    }

    vec4 fc;



    fc.rgb = vec3(sc,sc,sc);
    fc.a = 1.0;

    color = fc;

}
