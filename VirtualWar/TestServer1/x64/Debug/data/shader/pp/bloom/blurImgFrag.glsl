#version 330 core

in vec2 UV;
in vec4 col;

out vec4 color;

uniform sampler2D fb;

uniform float blur;
#define PI 3.1415926538

void main()
{

 
    vec2 uv = UV;
    uv.y = 1.0-uv.y;

    vec3 bc = vec3(0,0,0);

    float samples=0;


    for(float ai=1;ai<3;ai++){

    for(float ang=0;ang<360.0f;ang+=12){

        float as = ( ang * PI) / 180.0f;

        vec2 buv = uv;

        float na = ai * 0.002f;

        float nb = blur * ai;

        buv.x = buv.x + cos(as) * nb;
        buv.y = buv.y + sin(as) * nb;

        if(buv.x<0 || buv.y<0 || buv.x>1.0 || buv.y>1.0)
        {

        }else{

        bc = bc + texture2D(fb,buv).rgb;

        samples++;
        }
    }

    }

    bc = bc / (samples);

    vec4 texCol = vec4(bc.x,bc.y,bc.z,1.0);


    color = texCol;

}