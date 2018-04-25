#ifndef MYVERTEXSHADER_H
#define MYVERTEXSHADER_H

#include <iostream>
#include <glad\glad.h>
#include <glfw\glfw3.h>

using namespace std;

//  Phong 顶点着色器源代码
const char* objVertexShaderSource_Phong =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 fragPos;\n"
"out vec3 normal;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
"	fragPos = vec3(model * vec4(aPos, 1.0f));\n"
"	normal = mat3(transpose(inverse(model))) * aNormal;\n"
"}\0";

//  Gouraud顶点着色器源代码
const char* objVertexShaderSource_Gouraud =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"uniform vec3 viewPos;\n"
"uniform vec3 lightPos;\n"
"uniform vec3 lightColor;\n"
"uniform vec3 objColor;\n"
"out vec3 outColor;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
"	vec3 fragPos = vec3(model * vec4(aPos, 1.0f));\n"
"	vec3 normal = mat3(transpose(inverse(model))) * aNormal;\n"
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
"	outColor = (ambient+diffuse+specular) * objColor;\n"
"}\0";


//  光照立方体源代码
const char* lightVertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"}\0";



class myVertexShader {
public:
	myVertexShader(int shaderType);
	~myVertexShader();
	bool createVertexShader(int shaderType);
	unsigned int& getVertexShader();
	bool isSucceed();
	void deleteShader();
private:
	unsigned int vertexShader;
};

myVertexShader::myVertexShader(int shaderType = 0) {
	vertexShader = 0;
	createVertexShader(shaderType);
}

myVertexShader::~myVertexShader() {
	vertexShader = 0;
}

bool myVertexShader::createVertexShader(int shaderType) {
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShader == 0) {
		cout << "Failed to create vertex shader." << endl;
		return false;
	}
	if (shaderType == 0) {
		glShaderSource(vertexShader, 1, &objVertexShaderSource_Phong, NULL);
	} else if (shaderType == 1){
		glShaderSource(vertexShader, 1, &objVertexShaderSource_Gouraud, NULL);
	} else {
		glShaderSource(vertexShader, 1, &lightVertexShaderSource, NULL);
	}

	//  编译Vertex Shader，检测是否error
	int success;
	char infoLog[512];
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		return false;
	}

	return true;
}

bool myVertexShader::isSucceed() {
	return !(vertexShader == 0);
}

unsigned int& myVertexShader::getVertexShader() {
	return vertexShader;
}

void myVertexShader::deleteShader() {
	glDeleteShader(vertexShader);
	vertexShader = 0;
}
#endif
