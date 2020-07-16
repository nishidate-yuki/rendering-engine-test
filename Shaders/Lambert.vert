#version 330

// world transform / view-proj
uniform mat4 uModel;
uniform mat4 uViewProj;

// position, normal, tex coords.
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

// position�ȊO�̏o��
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragWorldPos;

void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	pos = uModel * pos;
	fragWorldPos = pos.xyz;
	gl_Position = uViewProj * pos;

	// w=0�Ƃ��ĕ��s�ړ��𖳌�������
	// ���l�X�P�[�����O���s���ꍇ�͖@���s��������ƌv�Z����K�v������
	fragNormal = (uModel * vec4(inNormal, 0.0f)).xyz;

	fragTexCoord = inTexCoord;
}
