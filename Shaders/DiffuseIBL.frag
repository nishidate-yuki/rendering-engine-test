#version 330

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
uniform sampler2D uTexture;
uniform DirectionalLight uDirLight;

// åªèÛÇÕNormalMappingÇ»ÇµÇ…ÇµÇƒÇ¢ÇÈ
void main()
{
	vec3 N = normalize(fragNormal);

	vec3 ambient = texture(irradianceMap, N).rgb;

	vec3 Diffuse = ambient;

    outColor = texture(uTexture, fragTexCoord);
	outColor *= vec4(Diffuse, 1.0);
}
