#version 430 core
out vec4 Fragcolor;
in vec3 localPos;
uniform samplerCube environmentMap;

const float PI= 3.14159265359;

void main(){
	// World space vector
    vec3 N = normalize(localPos);

    vec3 irradiance = vec3(0.0);

    // Basis vectors
    vec3 up    = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(up, N);
    up = cross(N, right);

    float delta = 0.025;
    float nSamples = 0.0;
    for(float phi = 0.0; phi < 2.0 * PI; phi +=delta){
        for(float theta = 0.0; theta < 0.5 * PI; theta +=delta){
            // 球座標 -> デカルト座標(Tanget space)
            vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
            // Tangent space -> World space
            vec3 sampleDir = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N;

            irradiance += texture(environmentMap, sampleDir).rgb * cos(theta) * sin(theta);
            nSamples++;
        }
    }
    irradiance = PI * irradiance * (1.0 / float(nSamples));
    Fragcolor = vec4(irradiance, 1.0);
}