#version 330
const float PI= 3.14159265359;

struct DirectionalLight
{
	vec3 color;
	float intensity;
	vec3 direction;
};

float DistributionGGX(vec3 N, vec3 H, float a)
{
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom    = a2;
    float denom  = (NdotH2 * (a2 - 1.0) + 1.0);
    denom        = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float k)
{
    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float k)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, k);
    float ggx2 = GeometrySchlickGGX(NdotL, k);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;
in mat3 TBN;

out vec4 outColor;

uniform vec3 camPos;
uniform samplerCube irradianceMap;
uniform sampler2D albedoMap;
uniform sampler2D emissiveMap;
uniform sampler2D normalMap;
uniform sampler2D AOMap;
uniform sampler2D metalRoughMap;
uniform DirectionalLight uDirLight;

// 現状はNormalMapping無し
// 反射の後にNormalMappingをした方が違いが分かりやすい
void main()
{
	vec3 normal = normalize(2.0 * texture(normalMap, fragTexCoord).rgb - 1.0);
    normal = normalize(TBN * normal);
	vec3 N = normalize(normal);
//	vec3 N = normalize(fragNormal);

	vec3 V = normalize(camPos - fragWorldPos);
    vec3 R = reflect(-V, N);

	vec3 ambient = texture(irradianceMap, N).rgb;

	vec3 Diffuse = ambient;

    outColor = texture(albedoMap, fragTexCoord);
	outColor *= vec4(Diffuse, 1.0);
}
