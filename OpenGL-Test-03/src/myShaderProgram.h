#ifndef MYSHADERPROGRAM_H
#define MYSHADERPROGRAM_H

#include <iostream>
#include <glad\glad.h>
#include <glfw\glfw3.h>

using namespace std;

class myShaderProgram {
public:
	myShaderProgram();
	~myShaderProgram();
	bool createShaderProgram();
	bool shaderProgramTest();
	bool isSucceed();
	int& getShaderProgram();
private:
	int shaderProgram;
};


myShaderProgram::myShaderProgram() {
	shaderProgram = 0;
	createShaderProgram();
}
myShaderProgram::~myShaderProgram() {
	shaderProgram = 0;
}

bool myShaderProgram::createShaderProgram() {
	shaderProgram = glCreateProgram();
	if (&shaderProgram == 0) {
		cout << "Failed to create shader program." << endl;
		return false;
	}
	return true;
}

bool myShaderProgram::shaderProgramTest() {
	int success = 0;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "RROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		return false;
	}
	return true;
}

int& myShaderProgram::getShaderProgram() {
	return shaderProgram;
}

bool myShaderProgram::isSucceed() {
	return !(shaderProgram == 0);
}


#endif

