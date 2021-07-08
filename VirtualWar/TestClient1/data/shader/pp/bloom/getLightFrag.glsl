    #version 330 core

in vec2 UV;
in vec4 col;

out vec4 color;

uniform sampler2D fb;
uniform float tH;

void main()
{

    vec2 uv = UV;
    uv.y = 1.0-uv.y;

    vec4 texCol = texture2D(fb,uv);

    float tV = texCol.x + texCol.y + texCol.z;

    tV = tV / 3.0;

    if(tV<tH)
    {

        texCol = vec4(0,0,0,1);

    }
    

    color = texCol;


}