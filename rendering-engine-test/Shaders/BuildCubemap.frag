#version 430 core
out vec4 FragColor;
in vec3 localPos;

uniform sampler2D hdri;

// 0.1591 = 1/(2pi)
// 0.3183 = 1/(pi)
const vec2 invAtan = vec2(0.1591, 0.3183);
vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv = uv * invAtan + 0.5;	// radian -> uv
    return uv;
}

void main()
{
    vec2 uv = SampleSphericalMap(normalize(localPos));
    vec3 color = texture(hdri, uv).rgb;

    FragColor = vec4(color, 1.0);
}
