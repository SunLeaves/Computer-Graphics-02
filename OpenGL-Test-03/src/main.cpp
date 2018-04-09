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
#include "myGUI.h"
#include "myTransform.h"

#define INIT_WIDTH 900
#define INIT_HEIGHT 900

using namespace std;

float vertices[36][6] = {0};

int main() {
	GLFWwindow* window = NULL;
	myVertexShader* vertexShader = NULL;
	myFragmentShader* fragmentShader = NULL;
	myShaderProgram* shaderProgram = NULL;
	myGUI* mygui = NULL;

	unsigned int mVAO = 0;
	unsigned int mVBO = 0;

	// 矩阵
	glm::mat4 scale;
	glm::mat4 trans;
	glm::mat4 rotate;
	glm::mat4 identity;
	rotate = glm::rotate(rotate, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 1.0f));

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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//  获取uniform位置
	int scaleLoc = glGetUniformLocation(shaderProgram->getShaderProgram(), "scale"),
		transLoc = glGetUniformLocation(shaderProgram->getShaderProgram(), "trans"),
		rotateLoc = glGetUniformLocation(shaderProgram->getShaderProgram(), "rotate");

	//  更新uniform值
	glUseProgram(shaderProgram->getShaderProgram());
	glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, &scale[0][0]);
	glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, &rotate[0][0]);
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, &trans[0][0]);

	//  绑定GUI到window窗口
	mygui = new myGUI();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsClassic();

	//  启用深度测试
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	float nowTime = 0.0f, rest = 0.0f;

	//  渲染循环
	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//  创建GUI界面
		ImGui_ImplGlfwGL3_NewFrame();
		mygui->createOptions();
		
		glUseProgram(shaderProgram->getShaderProgram());

		switch (mygui->getTransSelected())
		{
		case 0:
			changeMatrix(trans, 0);
			scale = identity;
			glUniformMatrix4fv(transLoc, 1, GL_FALSE, &trans[0][0]);
			glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, &scale[0][0]);
			break;
		case 1:
			trans = identity;
			changeMatrix(scale, 1);
			glUniformMatrix4fv(transLoc, 1, GL_FALSE, &trans[0][0]);
			glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, &scale[0][0]);
			break;
		case 2:
			trans = identity;
			changeMatrix(scale, 2);
			glUniformMatrix4fv(transLoc, 1, GL_FALSE, &trans[0][0]);
			glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, &scale[0][0]);
			break;
		case 3:
			changeMatrix(rotate, 3);
			scale = trans = identity;
			glUniformMatrix4fv(transLoc, 1, GL_FALSE, &trans[0][0]);
			glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, &scale[0][0]);
			glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, &rotate[0][0]);
			break;
		default:
			break;
		}

		glDrawArrays(GL_TRIANGLES, 0, 36);
		mygui->render();

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