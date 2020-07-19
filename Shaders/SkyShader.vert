#version 430 core
layout (location = 0) in vec3 aPos;

out vec3 localPos;

uniform mat4 uViewProj;

void main()
{
    localPos = aPos;
    gl_Position =  uViewProj * vec4(localPos, 1.0);
}