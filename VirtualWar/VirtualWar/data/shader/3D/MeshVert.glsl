#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec4 vCol;
layout(location = 2) in vec3 vUv;
layout(location = 3) in vec3 vNorm;
layout(location = 4) in vec3 vBiNorm;
layout(location = 5) in vec3 vTan;

uniform mat4 mProj;
uniform mat4 mModel;
uniform mat4 mView;
uniform vec3 viewPos;
uniform vec3 lPos;

out vec3 oUv;
out vec4 oCol;
out vec3 oFragPos;
out vec3 TLP;
out vec3 TVP;
out vec3 TFP;
out vec3 rPos;
out vec3 oNorm;
out vec3 reflectVector;
out vec3 pass_normal;
out mat3 normMat;
out mat3 TBN;

void main(){

    oUv = vUv;
    oCol = vCol;

    oFragPos = vec3(mModel * vec4(vPos,1.0));

    mat3 normalMatrix = transpose(inverse(mat3(mModel)));

    normMat = normalMatrix;

    vec3 T = normalize(normalMatrix * vTan);
	vec3 N = normalize(normalMatrix * vNorm);

	vec4 worldPos = mModel * vec4(vPos,1.0);

	pass_normal = N;

    //
    
    vec3 unitNormal = normalize(N);

	vec3 viewVector = normalize(worldPos.xyz - viewPos);

	reflectVector = reflect(viewVector, unitNormal);

	oNorm = vPos;
	
	T = normalize(T-dot(T,N) *N);
	
	vec3 B = cross(N,T);

	TBN = transpose(mat3(T,B,N));


	TLP = TBN * lPos;
	TVP = TBN * viewPos;
	TFP = TBN * oFragPos;

    gl_Position = mProj * mView *mModel* vec4(vPos,1.0);

}