uniform sampler2D fb;
uniform sampler2D deform;



void main()
{

    vec2 duv = gl_TexCoord[0].st;

    vec2 nuv = duv;
    nuv.y = 1.0 - nuv.y;
 //   duv.y = 1.0 - duv.y;

    vec3 dc = texture2D(deform,nuv).rgb;

    dc.x = -1.0 + dc.x * 2.0;
    dc.y = -1.0 + dc.y * 2.0;

    dc = dc * 0.03;

    vec3 fc = texture2D(fb,duv+dc).rgb;

 
    



    gl_FragColor = vec4(fc.r,fc.g,fc.b,1.0);

}