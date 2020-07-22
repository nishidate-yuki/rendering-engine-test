#version 430

struct DirectionalLight
{
	vec3 color;
	float intensity;
	vec3 direction;
};

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;
in mat3 TBN;

out vec4 outColor;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D emissiveMap;
uniform sampler2D AOMap;
uniform sampler2D metalRoughMap;
uniform DirectionalLight uDirLight;

void main()
{
	vec3 normal = normalize(2.0 * texture(normalMap, fragTexCoord).rgb - 1.0);
    normal = normalize(TBN * normal);

	vec3 N = normalize(normal);
	vec3 L = - normalize(uDirLight.direction);
	vec3 Diffuse = vec3(dot(N, L));

    outColor = texture(diffuseMap, fragTexCoord);
	outColor *= vec4(Diffuse, 1.0);
}
