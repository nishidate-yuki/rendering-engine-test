#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;

out vec4 outColor;

uniform sampler2D uTexture;

struct DirectionalLight
{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
};

// Uniforms for lighting
// Camera position (in world space)
//uniform vec3 uCameraPos;
// Specular power for this surface
//uniform float uSpecPower;
// Ambient light level
//uniform vec3 uAmbientLight;

// Directional Light
//uniform DirectionalLight uDirLight;

void main()
{
	// Surface normal
//	vec3 N = normalize(fragNormal);
//	// Vector from surface to light
//	vec3 L = normalize(-uDirLight.mDirection);
//	// Vector from surface to camera
//	vec3 V = normalize(uCameraPos - fragWorldPos);
//	// Reflection of -L about N
//	vec3 R = normalize(reflect(-L, N));
//
//	// Compute phong reflection
//	vec3 Phong = uAmbientLight;
//	float NdotL = dot(N, L);
//	if (NdotL > 0)
//	{
//		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;
//		vec3 Specular = uDirLight.mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);
//		Phong += Diffuse + Specular;
//	}

	// Final color is texture color times phong light (alpha = 1)
//    outColor = texture(uTexture, fragTexCoord) * vec4(Phong, 1.0f);
    outColor = vec4(fragNormal+0.5, 1.0);
}
