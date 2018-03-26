#include <iostream>
#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>

#include "myWIndow.h"
#include "myVertexShader.h"
#include "myFragmentShader.h"
#include "myShaderProgram.h"
#include "myTriangle.h"
#include "myCircle.h"
#include "myGUI.h"

#define INIT_WIDTH 1000
#define INIT_HEIGHT 1000

using namespace std;

int triPoints[12000] = { 0 };
int triCount = 0;
int triVertices[3][2] = { 0 };

int circlePoints[16000] = { 0 };
int cirCenter[2] = { 0, 0 };
int cirRadius = 100;
int cirCount = 0;

void drawTriangle() {
	triCount = 0;
	createTriangle(triVertices[0], triVertices
		[1], triVertices[2], triCount, triPoints);

}

void drawCircle() {
	cirCount = 0;
	createCircle(cirCenter, cirRadius, cirCount, circlePoints);
}

void draw(myGUI* (&mygui)) {
	int flag = mygui->getRadiochecked();
	switch (flag) {
	case 0:
		mygui->getTriVertices(triVertices);
		drawTriangle();
		break;
	case 1:
		mygui->getCenter(cirCenter);
		mygui->getRadius(cirRadius);
		drawCircle();
		break;
	default:
		break;
	}
}

int main() {

	GLFWwindow* window = NULL;
	myVertexShader* vertexShader = NULL;
	myFragmentShader* fragmentShader = NULL;
	myShaderProgram* shaderProgram = NULL;

	unsigned int mVBO = 0;
	unsigned int mVAO = 0;

	//  ���������ζ�������
	drawTriangle();
	//  testCircle();

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
	if (!fragmentShader->isSucceed()) {
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

	//  ���ɰ�VAO��VBO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	//  ���ƶ������ݵ������ڴ���
	//  glBufferData(GL_ARRAY_BUFFER, sizeof(triPoints), triPoints, GL_STATIC_DRAW);
	//  glBufferData(GL_ARRAY_BUFFER, sizeof(circlePoints), circlePoints, GL_STATIC_DRAW);

	//  ���Ӷ������Բ�������
	glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 2 * sizeof(GL_INT), (void*)0);
	glEnableVertexAttribArray(0);

	//  window��GUI,����GUI����
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsClassic();
	myGUI* mygui = new myGUI();

	//  ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(0.8f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplGlfwGL3_NewFrame();

		glUseProgram(shaderProgram->getShaderProgram());
		//  ����GUI
		mygui->createOptions();
		draw(mygui);
		if (mygui->getRadiochecked() == 0){
			glBufferData(GL_ARRAY_BUFFER, sizeof(triPoints), triPoints, GL_STATIC_DRAW);
			glDrawArrays(GL_POINTS, 0, triCount / 2);
		} else {
			glBufferData(GL_ARRAY_BUFFER, sizeof(circlePoints), circlePoints, GL_STATIC_DRAW);
			glDrawArrays(GL_POINTS, 0, cirCount / 2);
		}
		ImGui::Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);

	glfwTerminate();

	delete mygui;
	delete shaderProgram;
	delete fragmentShader;
	delete vertexShader;
	system("pause");
	return 0;

}