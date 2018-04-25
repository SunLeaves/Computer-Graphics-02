#ifndef MYFRAGMENTSHADER_H
#define MYFRAGMENTSHADER_H

#include <iostream>
#include <glad\glad.h>
#include <glfw\glfw3.h>

using namespace std;

//  Phong Shading着色器程序源代码
const char* objFragShaderSource_Phong =
"#version 330 core\n"
"uniform vec3 viewPos;\n"
"uniform vec3 lightPos;\n"
"uniform vec3 lightColor;\n"
"uniform vec3 objColor;\n"
"in vec3 fragPos;\n"
"in vec3 normal;\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
"	float ambientStrength = 0.1f;\n"
"	vec3 ambient = ambientStrength * lightColor;\n"
"	vec3 stdNormal = normalize(normal);\n"
"	vec3 lightDir = normalize(lightPos-fragPos);\n"
"	float diff = max(dot(stdNormal, lightDir), 0.0f);\n"
"	vec3 diffuse = diff * lightColor;\n"
"	float specularStrength = 0.5f;\n"
"	vec3 viewDir = normalize(viewPos - fragPos);\n"
"	vec3 reflectDir = reflect(-lightDir, stdNormal);\n"
"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);\n"
"	vec3 specular = specularStrength * spec * lightColor;\n"
"	vec3 result = (ambient+diffuse+specular) * objColor;\n"
"	fragColor = vec4(result, 1.0f);\n"
"}\n\0";

//  Gouraud Shading 着色器源代码
const char* objFragShaderSource_Gouraud =
"#version 330 core\n"
"in vec3 outColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(outColor, 1.0f);\n"
"}\n\0";

//  光源立方体着色器
const char* lightFragShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";


class myFragmentShader {
public:
	myFragmentShader(int shaderType);
	~myFragmentShader();
	bool createFragmentShader(int shaderType);
	unsigned int& getFragmentShader();
	bool isSucceed();
	void deleteShader();
private:
	unsigned int fragmentShader;
};

myFragmentShader::myFragmentShader(int shaderType = 0) {
	fragmentShader = 0;
	createFragmentShader(shaderType);
}

myFragmentShader::~myFragmentShader() {
	fragmentShader = 0;
}

bool myFragmentShader::createFragmentShader(int shaderType) {
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) {
		cout << "Failed to create a fragment shader." << endl;
		return false;
	}

	//  根据着色器类型使用着色器源码，编译Fragment Shader，检测是否error
	if (shaderType == 0) {
		glShaderSource(fragmentShader, 1, &objFragShaderSource_Phong, NULL);
	} else if (shaderType == 1) {
		glShaderSource(fragmentShader, 1, &objFragShaderSource_Gouraud, NULL);
	} else {
		glShaderSource(fragmentShader, 1, &lightFragShaderSource, NULL);
	}

	int success;
	char infoLog[512];
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
		return false;
	}

	return true;
}

unsigned int& myFragmentShader::getFragmentShader() {
	return fragmentShader;
}

bool myFragmentShader::isSucceed() {
	return !(fragmentShader == 0);
}

void myFragmentShader::deleteShader() {
	glDeleteShader(fragmentShader);
	fragmentShader = 0;
}

#endif
