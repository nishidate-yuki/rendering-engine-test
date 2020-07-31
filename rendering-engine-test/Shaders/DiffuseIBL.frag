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

uniform vec3 camPos;
uniform samplerCube irradianceMap;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D emissiveMap;
uniform sampler2D AOMap;
uniform sampler2D metalRoughMap;
uniform DirectionalLight uDirLight;

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

// åªèÛÇÕNormalMappingñ≥Çµ
// îΩéÀÇÃå„Ç…NormalMappingÇÇµÇΩï˚Ç™à·Ç¢Ç™ï™Ç©ÇËÇ‚Ç∑Ç¢
void main()
{
    vec3  albedo     = texture(albedoMap, fragTexCoord).rgb;
//    vec3  emissive   = texture(emissiveMap, fragTexCoord).rgb;
    vec3  normal     = texture(normalMap, fragTexCoord).rgb;
    float ao         = texture(AOMap, fragTexCoord).r;
    vec2  metalRough = texture(metalRoughMap, fragTexCoord).bg;
    float metallic   = metalRough.x;
//    float roughness  = metalRough.y;

	vec3 N = normalize(fragNormal);
	vec3 V = normalize(camPos - fragWorldPos);

	vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    vec3 kS = fresnelSchlick(max(dot(N, V), 0.0), F0);
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;
    vec3 irradiance = texture(irradianceMap, N).rgb;
    vec3 diffuse = irradiance * albedo;
    vec3 ambient = (kD * diffuse) * ao;

	vec3 color = ambient;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

	outColor = vec4(color, 1.0);
}
