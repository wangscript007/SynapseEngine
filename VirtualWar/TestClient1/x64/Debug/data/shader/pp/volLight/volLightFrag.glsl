uniform sampler2D fb;
uniform float tH;

void main()
{

    vec2 uv = gl_TexCoord[0].st;
    uv.y = 1.0-uv.y;

    vec4 texCol = texture2D(fb,uv);

   

    gl_FragColor = texCol;

}