#include <iostream>
#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


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

	//  旋转矩阵
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.0f, 1.0f, 1.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)INIT_WIDTH / INIT_HEIGHT, 0.1f, 100.0f);

	getPoints(vertices);

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
		cout << "Shader program error." << endl;
		glfwTerminate();
		return -1;
	}

	//  链接着色器
	glAttachShader(shaderProgram->getShaderProgram(), vertexShader->getVertexShader());
	glAttachShader(shaderProgram->getShaderProgram(), fragmentShader->getFragmentShader());
	glLinkProgram(shaderProgram->getShaderProgram());
	//  检测链接错误
	if (!shaderProgram->shaderProgramTest()) {
		cout << "Shader Program error." << endl;
		glfwTerminate();
		return -1;
	}
	//  删除着色器对象
	vertexShader->deleteShader();
	fragmentShader->deleteShader();

	//  生成VAO，VBO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	//  复制顶点数据到缓冲内存中，链接顶点属性
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	//  获取uniform位置
	int modelPosition = glGetUniformLocation(shaderProgram->getShaderProgram(), "model"),
		viewPosition = glGetUniformLocation(shaderProgram->getShaderProgram(), "view"),
		projectionPosition = glGetUniformLocation(shaderProgram->getShaderProgram(), "projection");
	//  更新uniform值
	glUseProgram(shaderProgram->getShaderProgram());
	glUniformMatrix4fv(modelPosition, 1, GL_FALSE, &model[0][0]);
	glUseProgram(shaderProgram->getShaderProgram());
	glUniformMatrix4fv(viewPosition, 1, GL_FALSE, &view[0][0]);
	glUseProgram(shaderProgram->getShaderProgram());
	glUniformMatrix4fv(projectionPosition, 1, GL_FALSE, &projection[0][0]);

	//  绑定GUI到window窗口
	//ImGui_ImplGlfwGL3_Init(window, true);
	//ImGui::StyleColorsClassic();

	//  启用深度测试
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//  渲染循环
	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(0.8f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//ImGui_ImplGlfwGL3_NewFrame();
		glUseProgram(shaderProgram->getShaderProgram());

		//  更新旋转矩阵
		//model = glGetUniformLocation(shaderProgram->getShaderProgram(), "projection");
		model = glm::rotate(model, (float)glfwGetTime()* 0.00001f, glm::vec3(0.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelPosition, 1, GL_FALSE, &model[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//  解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
	glfwTerminate();

	delete shaderProgram;
	delete fragmentShader;
	delete vertexShader;
	system("pause");
	return 0;

}