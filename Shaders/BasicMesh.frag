#version 330

// positionˆÈŠO‚Ì“ü—Í
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;

out vec4 outColor;

// for texture sampling
uniform sampler2D uTexture;

void main()
{
	// Sample color from texture
    outColor = texture(uTexture, fragTexCoord);
}
