#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 lightSpaceMatrix;

out vec3 fragPos;
out vec3 normal;

out vec4 fragPosLightSpace;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	fragPos = vec3(model * vec4(aPos, 1.0f));
	normal = (transpose(inverse(mat3(model)))) * aNormal;
	fragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0f);
}
