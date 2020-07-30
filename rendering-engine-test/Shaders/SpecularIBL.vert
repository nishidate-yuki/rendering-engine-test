#version 430

// world transform / view-proj
uniform mat4 model;
uniform mat4 viewProj;

// position, normal, tex coords.
layout(location = 0) in vec3 inPosition;	// model space
layout(location = 1) in vec3 inNormal;		// model space
layout(location = 2) in vec2 inTexCoord;

// position�ȊO�̏o��
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragWorldPos;

void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	pos = model * pos;
	fragWorldPos = pos.xyz;
	gl_Position = viewProj * pos;

	// w=0�Ƃ��ĕ��s�ړ��𖳌�������
	// ���l�X�P�[�����O���s���ꍇ�͖@���s��������ƌv�Z����K�v������
	fragNormal = (model * vec4(inNormal, 0.0f)).xyz;

	fragTexCoord = inTexCoord;
}
