#version 330
const float PI= 3.14159265359;

struct DirectionalLight
{
	vec3 color;
	float intensity;
	vec3 direction;
};

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;

out vec4 outColor;

uniform samplerCube irradianceMap;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D emissiveMap;
uniform sampler2D AOMap;
uniform sampler2D metalRoughMap;
uniform DirectionalLight uDirLight;

// Œ»ó‚ÍNormalMapping–³‚µ
// ”½Ë‚ÌŒã‚ÉNormalMapping‚ğ‚µ‚½•û‚ªˆá‚¢‚ª•ª‚©‚è‚â‚·‚¢
void main()
{
	vec3 N = normalize(fragNormal);

	vec3 ambient = texture(irradianceMap, N).rgb;

	vec3 Diffuse = ambient;

    outColor = texture(diffuseMap, fragTexCoord);
	outColor *= vec4(Diffuse, 1.0);
}
