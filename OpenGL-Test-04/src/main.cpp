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
#include "myTransform.h"
#include "myGUI.h"

#define INIT_WIDTH 900
#define INIT_HEIGHT 900

using namespace std;

int main() {
	float vertices[36][6] = { 0 };

	GLFWwindow* window = NULL;
	myVertexShader* vertexShader = NULL;
	myFragmentShader* fragmentShader = NULL;
	myShaderProgram* shaderProgram = NULL;
	myGUI* mygui = NULL;

	float clearColor[4] = { 0.8f, 0.8f, 0.9f, 1.0f };

	unsigned int mVAO = 0;
	unsigned int mVBO = 0;
	
	int modelLoc = 0,
		viewLoc = 0,
		projLoc = 0;


	//  矩阵
	glm::mat4 identity(1);
	glm::mat4 model(1);
	glm::mat4 view(1);
	glm::mat4 projection(1);

	//  设置顶点矩阵
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
	//  位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
	//  颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//  获取uniform变量位置
	modelLoc = glGetUniformLocation(shaderProgram->getShaderProgram(), "model");
	viewLoc = glGetUniformLocation(shaderProgram->getShaderProgram(), "view");
	projLoc = glGetUniformLocation(shaderProgram->getShaderProgram(), "projection");

	//  设置model、view、projection矩阵（初始化）
	glUseProgram(shaderProgram->getShaderProgram());
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	mygui = new myGUI();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsClassic();
	

	float eye[3] = { 0.0f, 10.0f, 10.0f };
	float clock = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram->getShaderProgram());


		ImGui_ImplGlfwGL3_NewFrame();
		mygui->createOptions();

		switch (mygui->funcSelected) {
		case 0:
			model = glm::translate(identity, glm::vec3(-1.5f, 0.5f, -1.5f));
			view = glm::lookAt(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.5f, 0.5f, -1.5f), glm::vec3(0.0f, 1.0f, 0.0f));
			projection = glm::ortho(mygui->orthPos[0], mygui->orthPos[1], mygui->orthPos[2], mygui->orthPos[3], mygui->orthDist[0], mygui->orthDist[1]);
			break;
		case 1:
			model = glm::translate(identity, glm::vec3(-1.5f, 0.5f, -1.5f));
			view = glm::lookAt(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.5f, 0.5f, -1.5f), glm::vec3(0.0f, 1.0f, 0.0f));
			projection = glm::perspective(glm::radians(mygui->perFov), mygui->srcRatio, mygui->orthDist[0], mygui->orthDist[1]);
			break;
		case 2:
			clock = glfwGetTime();
			eye[0] = sin(clock) * mygui->viewRadio;
			eye[1] = mygui->viewHeight;
			eye[2] = cos(clock) * mygui->viewRadio;
			model = identity;
			view = glm::lookAt(glm::vec3(eye[0], eye[1], eye[2]), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			projection = glm::perspective(glm::radians(mygui->perFov), mygui->srcRatio, mygui->orthDist[0], mygui->orthDist[1]);
			break;
		}
		
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		ImGui::Render();
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
	delete mygui;
	system("pause");
	return 0;
}