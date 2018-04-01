#include <iostream>
#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>

#include "myWindow.h"
#include "myVertexShader.h"
#include "myFragmentShader.h"
#include "myShaderProgram.h"

#define INIT_WIDTH 900
#define INIT_HEIGHT 900

using namespace std;

float vertices[36][3] = {0};

int main() {
	GLFWwindow* window = NULL;
	myVertexShader* vertexShader = NULL;
	myFragmentShader* fragmentShader = NULL;
	myShaderProgram* shaderProgram = NULL;

	unsigned int mVAO = 0;
	unsigned int mVBO = 0;

	getPoints(vertices);

	//  ��������
	if (!myCreateWindow(window, INIT_WIDTH, INIT_HEIGHT)) {
		return -1;
	}

	//  ����������ɫ��
	vertexShader = new myVertexShader();
	if (!vertexShader->isSucceed()) {
		glfwTerminate();
		return -1;
	}

	//  ����Ƭ����ɫ��
	fragmentShader = new myFragmentShader();
	if (fragmentShader->isSucceed()) {
		glfwTerminate();
		return -1;
	}

	//  ����Shader Program
	shaderProgram = new myShaderProgram();
	if (!shaderProgram->isSucceed()) {
		glfwTerminate();
		return -1;
	}

	//  ������ɫ��
	glAttachShader(shaderProgram->getShaderProgram(), vertexShader->getVertexShader());
	glAttachShader(shaderProgram->getShaderProgram(), fragmentShader->getFragmentShader());
	glLinkProgram(shaderProgram->getShaderProgram());
	//  ������Ӵ���
	if (!shaderProgram->shaderProgramTest()) {
		glfwTerminate();
		return -1;
	}
	//  ɾ����ɫ������
	vertexShader->deleteShader();
	fragmentShader->deleteShader();

	//  ����VAO��VBO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	//  ���ƶ������ݵ������ڴ��У����Ӷ�������
	//  wait for finished
	

	//  ��GUI��window����
	//ImGui_ImplGlfwGL3_Init(window, true);
	//ImGui::StyleColorsClassic();

	//  ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(0.8f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplGlfwGL3_NewFrame();
		glUseProgram(shaderProgram->getShaderProgram());



	}


}