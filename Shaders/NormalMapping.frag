#version 430

// structs
struct DirectionalLight
{
	vec3 color;
	float intensity;
	vec3 direction;
};

// positionˆÈŠO‚Ì“ü—Í
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;
in mat3 TBN;	// [Tan, BiTan, Norm] fro Normal mapping

out vec4 outColor;

// for texture sampling
uniform sampler2D uDiffuse;
uniform sampler2D uNormalMap;
uniform sampler2D uEmissiveMap;

// Light
uniform DirectionalLight uDirLight;

void main()
{
	vec3 normal = normalize(2.0 * texture(uNormalMap, fragTexCoord).rgb - 1.0);
    normal = normalize(TBN * normal); 

	vec3 N = normalize(normal);
	vec3 L = - normalize(uDirLight.direction);
	vec3 Diffuse = vec3(dot(N, L));

	// Sample color from texture
    outColor = texture(uDiffuse, fragTexCoord);
	outColor *= vec4(Diffuse, 1.0);
}
