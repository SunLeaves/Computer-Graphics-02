#include <iostream>
#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>

#include "myWIndow.h"
#include "myVertexShader.h"
#include "myFragmentShader.h"
#include "myShaderProgram.h"
#include "myCalLines.h"

#define INIT_WIDTH 800
#define INIT_HEIGHT 600

using namespace std;

int points[12000] = { 0 };
int pCount = 0;
int testPoints[200] = { 0 };



void test() {
	int A[2] = { 50, 100 };
	int B[2] = { 250, 600 };
	int C[2] = { 600, 300 };
	myCalLines(A, B, C, pCount, points);
}

int main() {

	GLFWwindow* window = NULL;
	myVertexShader* vertexShader = NULL;
	myFragmentShader* fragmentShader = NULL;
	myShaderProgram* shaderProgram = NULL;

	unsigned int mVBO = 0;
	unsigned int mVAO = 0;

	//  生成三角形顶点数据
	test();

	//  创建窗口
	if (!myCreateWindow(window, INIT_WIDTH, INIT_HEIGHT)) {
		return -1;
	}
	//  创建顶点着色器
	vertexShader = new myVertexShader();
	if (!vertexShader->isSucceed()) {
		glfwTerminate();
		return -1;
	}
	//  创建片段着色器
	fragmentShader = new myFragmentShader();
	if (!fragmentShader->isSucceed()) {
		glfwTerminate();
		return -1;
	}
	//  创建Shader Program
	shaderProgram = new myShaderProgram();
	if (!shaderProgram->isSucceed()) {
		glfwTerminate();
		return -1;
	}
	//  链接着色器
	glAttachShader(shaderProgram->getShaderProgram(), vertexShader->getVertexShader());
	glAttachShader(shaderProgram->getShaderProgram(), fragmentShader->getFragmentShader());
	glLinkProgram(shaderProgram->getShaderProgram());
	//  检测链接错误
	if (!shaderProgram->shaderProgramTest()) {
		glfwTerminate();
		return -1;
	}
	//  删除着色器对象
	vertexShader->deleteShader();
	fragmentShader->deleteShader();

	//  生成绑定VAO，VBO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	//  复制顶点数据到缓冲内存中
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	//  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//  链接顶点属性并其启用
	glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 2 * sizeof(GL_INT), (void*)0);
	//  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	//  绑定GUI

	//  渲染循环
	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(0.8f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glBufferData(GL_ARRAY_BUFFER, sizeof(testPoints), testPoints, GL_STATIC_DRAW);

		glUseProgram(shaderProgram->getShaderProgram());

		glDrawArrays(GL_POINTS, 0, pCount);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);

	glfwTerminate();

	//delete mygui;
	delete shaderProgram;
	delete fragmentShader;
	delete vertexShader;
	system("pause");
	return 0;

}