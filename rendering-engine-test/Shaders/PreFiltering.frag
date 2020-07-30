#version 430 core
out vec4 Fragcolor;
in vec3 localPos;

uniform samplerCube environmentMap;
uniform float roughness;

const float PI= 3.14159265359;
const uint  SAMPLE_COUNT = 1024u;

float RadicalInverse(uint bits);
vec2 Hammersley(uint i, float invN);
vec3 ImportanceSampleGGX(vec2 Xi, vec3 N, float roughness);

// ���͂��ꂽ���L���[�u�}�b�v���قȂ�e�����ƂɃt�B���^�����O����
// �t�B���^���ꂽ�}�b�v�̓~�b�v�}�b�v�Ƃ��ĕۑ������
void main(){
    // �L���[�u�̃t���O�����g�͒P�ʋ��̕\�ʂȂ̂ŁA
	// ���[���h���W�̕������@���ƂȂ�B�����N=R=V�Ƌߎ�����B
    vec3 N = normalize(localPos);
    vec3 R = N;
    vec3 V = R;

    float totalWeight = 0.0;
    vec3  prefilteredColor = vec3(0.0);

    for(uint i = 0u; i < SAMPLE_COUNT; ++i){
        vec2 Xi = Hammersley(i, 1.0/float(SAMPLE_COUNT));
        vec3 H  = ImportanceSampleGGX(Xi, N, roughness);
        vec3 L = normalize(2.0 * dot(V,H) * H - V);

        float nDotL = max(dot(N,L), 0.0);
        if(nDotL > 0.0){
            prefilteredColor += texture(environmentMap, L).rgb * nDotL;
            totalWeight += nDotL;
        }
    }

    prefilteredColor = prefilteredColor / totalWeight;

    Fragcolor = vec4(prefilteredColor, 1.0);
}

float RadicalInverse(uint bits){
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

vec2 Hammersley(uint i, float invN ){
    return vec2(float(i) * invN, RadicalInverse(i));
}

/**
 * GGX��p���ăn�[�t�x�N�g�����d�_�T���v�����O����
 */
vec3 ImportanceSampleGGX(vec2 Xi, vec3 N, float roughness){
    float a = roughness * roughness;

    float phi = 2.0 * PI * Xi.x;
    float cosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a * a - 1.0) * Xi.y));
    float sinTheta = sqrt(1.0 - cosTheta *cosTheta);

    // �����W���璼�����W�ɕϊ�
    vec3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    // Tangent space ���� world space
    vec3 up = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    vec3 tangent = normalize(cross(up, N));
    vec3 bitangent = cross(N, tangent);

    // Multiplaying halfway vector times implicit TBN matrix
    vec3 sampleVec = tangent * H.x + bitangent * H.y + N* H.z;
    return normalize(sampleVec);
}