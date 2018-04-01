#ifndef MYFRAGMENTSHADER_H
#define MYFRAGMENTSHADER_H

#include <iostream>
#include <glad\glad.h>
#include <glfw\glfw3.h>

using namespace std;

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);\n"
"}\n\0";;


class myFragmentShader {
public:
	myFragmentShader();
	~myFragmentShader();
	bool createFragmentShader();
	unsigned int& getFragmentShader();
	bool isSucceed();
	void deleteShader();
private:
	unsigned int fragmentShader;
};

myFragmentShader::myFragmentShader() {
	fragmentShader = 0;
	createFragmentShader();
}

myFragmentShader::~myFragmentShader() {
	fragmentShader = 0;
}

bool myFragmentShader::createFragmentShader() {
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) {
		cout << "Failed to create a fragment shader." << endl;
		return false;
	}

	//  ±àÒëFragment Shader£¬¼ì²âÊÇ·ñerror
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	int success;
	char infoLog[512];
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
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
