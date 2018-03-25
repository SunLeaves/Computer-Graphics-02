#include <iostream>
#include <sstream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>


#include "myWindow.h"
#include "myVertexShader.h"
#include "myFragmentShader.h"
#include "myShaderProgram.h"
#include "myGUI.h"

using namespace std;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main() {
	GLFWwindow* window = NULL;
	myVertexShader* vertexShader = NULL;
	myFragmentShader* fragmentShader = NULL;
	myShaderProgram* shaderProgram = NULL;

	float vertices[2][9] = {
		//  Positons;
		{ 
			-0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.5f
		},
		//  Color
		{
			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f
		}
		
	};
	unsigned int mVBO = 0;
	unsigned int mVAO = 0;

	//  创建窗口
	myCreateWindow(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (window == NULL) {
		glfwTerminate();
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

	//  链接Shaders
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


	//  生成VAO，绑定VAO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	//  生成VBO，绑定VBO
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	//  复制顶点数据到缓冲的内存中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//  链接顶点属性并启用
	//  位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	//  颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)(9*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	//  解绑
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

/*
**********************************************************************
*/
	//  window绑定GUI
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsClassic();

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

/*
**********************************************************************
*/
	myGUI* mygui = new myGUI();
	//  渲染循环
	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplGlfwGL3_NewFrame();

		//  创建Gui，并实时更新顶点数据
		{
			mygui->createOptions();
			mygui->updateVertices(vertices);
		}

		glUseProgram(shaderProgram->getShaderProgram());
		//  绑定缓冲内存
		//glBindVertexArray(mVAO);
		if (mygui->isChanged()) {
			//glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			mygui->resetChangedFlag();
		}
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//  调用ImGui::Render()进行渲染
		ImGui::Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);

	glfwTerminate();

	//  删除new的对象
	delete mygui;
	delete shaderProgram;
	delete fragmentShader;
	delete vertexShader;
	//system("pause");
	return 0;
}


