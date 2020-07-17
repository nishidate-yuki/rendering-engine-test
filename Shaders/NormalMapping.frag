#version 330

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

out vec4 outColor;

// for texture sampling
uniform sampler2D uTexture;

// Light
uniform DirectionalLight uDirLight;

void main()
{
	vec3 N = normalize(fragNormal);
	vec3 L = - normalize(uDirLight.direction);

	vec3 Diffuse = vec3(dot(N, L));

	// Sample color from texture
    outColor = texture(uTexture, fragTexCoord);
	outColor *= vec4(Diffuse, 1.0);
}
