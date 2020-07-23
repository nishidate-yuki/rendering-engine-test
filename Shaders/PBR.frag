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
uniform samplerCube envCubemap;
uniform samplerCube irradianceMap;

uniform sampler2D albedoMap;
uniform sampler2D emissiveMap;
uniform sampler2D normalMap;
uniform sampler2D AOMap;
uniform sampler2D metalRoughMap;

uniform DirectionalLight uDirLight;

// åªèÛÇÕNormalMappingñ≥Çµ
// îΩéÀÇÃå„Ç…NormalMappingÇÇµÇΩï˚Ç™à·Ç¢Ç™ï™Ç©ÇËÇ‚Ç∑Ç¢
void main()
{
    vec4 albedo     =  texture(albedoMap, fragTexCoord).rgba;
    vec3 emissive   =  texture(emissiveMap, fragTexCoord).rgb;
    float ao        =  texture(AOMap, fragTexCoord).r;
    vec2 metalRough =  texture(metalRoughMap, fragTexCoord).bg;
    float metallic  =  metalRough.x;
    float roughness =  metalRough.y;

    vec3 normal   =  texture(normalMap, fragTexCoord).rgb;
	normal = normalize(2.0 * normal.rgb - 1.0);
    normal = normalize(TBN * normal);
	vec3 N = normalize(normal);
//	vec3 N = normalize(fragNormal);

//	vec3 F0 = vec3(0.04);
//  F0 = mix(F0, albedo.rgb, metallic);
//
	vec3 V = normalize(camPos - fragWorldPos);
    vec3 R = reflect(-V, N);

	vec3 ambient = texture(irradianceMap, N).rgb;
	vec3 Diffuse = ambient;
//	outColor = albedo * vec4(Diffuse, 1.0);

	vec3 environment = texture(envCubemap, R).rgb;
	outColor = albedo * vec4(Diffuse, 1.0) + vec4(environment, 1.0) * metallic;
}
