#version 430
const float PI= 3.14159265359;
const float MAX_REFLECTION_LOD = 4.0;

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

uniform vec3 camPos;
uniform samplerCube envCubemap;
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;

uniform sampler2D albedoMap;
uniform sampler2D emissiveMap;
uniform sampler2D normalMap;
uniform sampler2D AOMap;
uniform sampler2D metalRoughMap;

uniform float time;

uniform DirectionalLight uDirLight;

float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 FresnelSchlick(float cosTheta, vec3 F0);
vec3 FresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness);


// åªèÛÇÕNormalMappingñ≥Çµ
// îΩéÀÇÃå„Ç…NormalMappingÇÇµÇΩï˚Ç™à·Ç¢Ç™ï™Ç©ÇËÇ‚Ç∑Ç¢
void main()
{
//    vec3  albedo     = texture(albedoMap, fragTexCoord).rgb;
    vec3  albedo     = pow(texture(albedoMap, fragTexCoord).rgb, vec3(2.2));
    vec3  emissive   = texture(emissiveMap, fragTexCoord).rgb;
    vec3  normal     = texture(normalMap, fragTexCoord).rgb;
    float ao         = texture(AOMap, fragTexCoord).r;
    vec2  metalRough = texture(metalRoughMap, fragTexCoord).bg;
    float metallic   = metalRough.x;
    float roughness  = metalRough.y;

	normal = normalize(2.0 * normal.rgb - 1.0);
    normal = normalize(TBN * normal);
	vec3 N = normalize(normal);
//	vec3 N = normalize(fragNormal);

	vec3 V = normalize(camPos - fragWorldPos);
	vec3 R = reflect(-V, N);

	vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

	float lodLevel = roughness * MAX_REFLECTION_LOD;
	vec3 prefilteredColor = textureLod(prefilterMap, R, lodLevel).rgb;

	float NdotV    = max(dot(N, V), 0.0);	// LUTÇÃxç¿ïW
	vec3  F        = FresnelSchlickRoughness(NdotV, F0, roughness);
	vec2  envBRDF  = texture(brdfLUT, vec2(NdotV, roughness)).rg;	 // BRDF LUTÇ©ÇÁíléÊìæ
	vec3  specular = prefilteredColor * (F * envBRDF.x + envBRDF.y);

	// diffuse Ç∆ specular ÇÃåWêî
	vec3 kS = F;
	vec3 kD = 1.0 - kS;
	kD *= 1.0 - metallic;

	vec3 irradiance = texture(irradianceMap, N).rgb;
	vec3 diffuse    = irradiance * albedo;

	vec3 ambient = (kD * diffuse + specular) * ao;

	vec3 color = ambient + emissive;

    color = color / (color + vec3(1.0));	// HDR tonemapping
    color = pow(color, vec3(1.0/2.2));		// gamma correct
    outColor = vec4(vec3(color), 1.0);
}


// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
// ----------------------------------------------------------------------------
vec3 FresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}
