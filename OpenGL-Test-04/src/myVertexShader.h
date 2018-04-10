#ifndef MYVERTEXSHADER_H
#define MYVERTEXSHADER_H

#include <iostream>
#include <glad\glad.h>
#include <glfw\glfw3.h>

using namespace std;


const char* vertextShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 outColor;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"	outColor = aColor;\n"
"   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"}\0"; 


class myVertexShader {
public:
	myVertexShader();
	~myVertexShader();
	bool createVertexShader();
	unsigned int& getVertexShader();
	bool isSucceed();
	void deleteShader();
private:
	unsigned int vertexShader;
};

myVertexShader::myVertexShader() {
	vertexShader = 0;
	createVertexShader();
}

myVertexShader::~myVertexShader() {
	vertexShader = 0;
}

bool myVertexShader::createVertexShader() {
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShader == 0) {
		cout << "Failed to create vertex shader." << endl;
		return false;
	}
	glShaderSource(vertexShader, 1, &vertextShaderSource, NULL);

	//  ±àÒëVertex Shader£¬¼ì²âÊÇ·ñerror
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
