#version 330 core

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objColor;

uniform float ambientFactor;
uniform float specularFactor;
uniform float diffuseFactor;
uniform int shininess;

uniform float bias;

uniform sampler2D shadowMap;

in vec3 fragPos;
in vec3 normal;

in vec4 fragPosLightSpace;

out vec4 fragColor;


float CalculateShadow() {

	//  ͸�ӳ���
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	//  �任xyz������ [0, 1]
	projCoords = projCoords * 0.5 + 0.5;

	if (projCoords.z > 1.0) {
		return 0.0f;
	}

	//  ��ȡ��λ����Ұ�µ�������
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	//  ƬԪ�ĵ�ǰ���
	float currentDepth = projCoords.z;

	//  �Ƚ�
	float shadow = (currentDepth - bias > closestDepth) ? 1.0 : 0.0;

	return shadow;
}

void main()
{
	vec3 ambient = ambientFactor * lightColor;

	vec3 stdNormal = normalize(normal);
	vec3 lightDir = normalize(lightPos-fragPos);
	float diff = max(dot(stdNormal, lightDir), 0.0f);
	vec3 diffuse = diffuseFactor * diff * lightColor;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, stdNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = specularFactor * spec * lightColor;

	float shadow = CalculateShadow();
	vec3 result = ( ambient + (1.0 - shadow) * (diffuse + specular)) * objColor;

	fragColor = vec4(result, 1.0f);
}




