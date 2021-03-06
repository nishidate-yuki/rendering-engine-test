#version 430

// world transform / view-proj
uniform mat4 model;
uniform mat4 viewProj;

// position, normal, tex coords.
layout(location = 0) in vec3 inPosition;	// model space
layout(location = 1) in vec3 inNormal;		// model space
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inTangent;		// model space ?
layout(location = 4) in vec3 inBiTangent;	// model space ?

// position以外の出力
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragWorldPos;
out mat3 TBN;

void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	pos = model * pos;
	fragWorldPos = pos.xyz;
	gl_Position = viewProj * pos;

	// w=0として平行移動を無効化する
	// 非一様スケーリングを行う場合は法線行列をちゃんと計算する必要がある
	fragNormal = (model * vec4(inNormal, 0.0f)).xyz;

	// for Normal mapping
	vec3 T = normalize(vec3(model * vec4(inTangent,   0.0)));
    vec3 B = normalize(vec3(model * vec4(inBiTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(inNormal,    0.0)));
    TBN = mat3(T, B, N);

	fragTexCoord = inTexCoord;
}
