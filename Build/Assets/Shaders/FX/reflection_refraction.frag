#version 430 core

in vec3 refraction_dir;
in vec3 reflection_dir;

out vec4 fcolor;

uniform float interpolation;

layout (binding = 0) uniform samplerCube cubeMap; //cube map

void main()
{
	fcolor = texture(cubeMap, refraction_dir);
	vec3 reflect_color = texture(cubeMap, reflection_dir).rgb;
	vec3 refract_color = texture(cubeMap, refraction_dir).rgb;

	vec3 color = mix(reflect_color, refract_color, interpolation);
	fcolor = vec4(color, 1);
// set fragment color
}
