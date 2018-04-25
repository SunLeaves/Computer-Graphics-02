#version 330 core

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objColor;

uniform float ambientFactor;
uniform float specularFactor;
uniform float diffuseFactor;
uniform int shininess;

in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

void main()
{
	vec3 ambient = lightColor;

	vec3 stdNormal = normalize(normal);
	vec3 lightDir = normalize(lightPos-fragPos);
	float diff = max(dot(stdNormal, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, stdNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = spec * lightColor;

	vec3 result = ( ambientFactor*ambient+diffuseFactor*diffuse+specularFactor*specular) * objColor;

	fragColor = vec4(result, 1.0f);
}