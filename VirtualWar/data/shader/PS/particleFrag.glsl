#version 330 core


in vec3 oUv;
in vec3 oCol;
in vec3 oExt;

uniform sampler2D tCol;

out vec4 color;

void main(){

    vec4 fc;
    fc.rgb = texture2D(tCol,oUv.xy).rgb;
    fc.a =texture2D(tCol,oUv.xy).a * oExt.r;
    fc.rgb = fc.rgb * vec3(fc.a,fc.a,fc.a);
    fc.rgb = fc.rgb * oCol;
    if(fc.a<0.2){
        discard;
        return;
    }



     color = fc;

}