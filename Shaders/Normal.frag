#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;

out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
    outColor = vec4(fragNormal+0.5, 1.0);
}
