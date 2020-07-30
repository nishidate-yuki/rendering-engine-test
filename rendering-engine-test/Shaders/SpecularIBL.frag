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

out vec4 outColor;

uniform vec3 camPos;

// IBLのために事前計算したテクスチャ
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D   brdfLUT;

uniform sampler2D albedoMap;
uniform sampler2D emissiveMap;
uniform sampler2D normalMap;
uniform sampler2D AOMap;
uniform sampler2D metalRoughMap;

uniform DirectionalLight uDirLight;

float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 FresnelSchlick(float cosTheta, vec3 F0);
vec3 FresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness);

// 現状はNormalMapping無し
// 反射の後にNormalMappingをした方が違いが分かりやすい
void main()
{
    vec4  albedo     =  texture(albedoMap, fragTexCoord).rgba;
    vec3  emissive   =  texture(emissiveMap, fragTexCoord).rgb;
    float ao         =  texture(AOMap, fragTexCoord).r;
    vec2  metalRough =  texture(metalRoughMap, fragTexCoord).bg;
    float metallic   =  metalRough.x;
    float roughness  =  metalRough.y;

	vec3 N = normalize(fragNormal);
	vec3 V = normalize(camPos - fragWorldPos);
	vec3 R = reflect(-V, N);

	// mix(x, y, a): xとyを線形補間する
	vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo.rgb, metallic);

	vec3 prefilteredColor = textureLod(prefilterMap, R, roughness * MAX_REFLECTION_LOD).rgb;

	float NdotV    = max(dot(N, V), 0.0);	// LUTのx座標
	vec3  F        = FresnelSchlickRoughness(NdotV, F0, roughness);
	vec2  envBRDF  = texture(brdfLUT, vec2(NdotV, roughness)).rg;	 // BRDF LUTから値取得
	vec3  specular = prefilteredColor * (F * envBRDF.x + envBRDF.y);

	// diffuse と specular の係数
	vec3 kS = F;
	vec3 kD = 1.0 - kS;
	kD *= 1.0 - metallic;

	vec3 irradiance = texture(irradianceMap, N).rgb;
	vec3 diffuse    = irradiance * albedo.rgb;

	vec3 ambient = (kD * diffuse + specular);	// without AO
//	vec3 ambient = (kD * diffuse + specular) * ao;	// with AO

	vec3 color = ambient;
    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2));
    outColor = vec4(color , 1.0);

//    outColor = texture(albedoMap, fragTexCoord);
//	outColor *= vec4(diffuse, 1.0);
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
