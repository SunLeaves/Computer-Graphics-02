#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objColor;

uniform float ambientFactor;
uniform float specularFactor;
uniform float diffuseFactor;
uniform int shininess;

out vec3 outColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);

	vec3 fragPos = vec3(model * vec4(aPos, 1.0f));
	vec3 normal = mat3(transpose(inverse(model))) * aNormal;
	vec3 ambient = ambientFactor * lightColor;

	vec3 stdNormal = normalize(normal);
	vec3 lightDir = normalize(lightPos-fragPos);
	float diff = max(dot(stdNormal, lightDir), 0.0f);
	vec3 diffuse = diffuseFactor * diff * lightColor;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, stdNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	vec3 specular = specularFactor * spec * lightColor;

	outColor = (ambient+diffuse+specular) * objColor;
}