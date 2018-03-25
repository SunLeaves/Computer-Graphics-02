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

	//  ��������
	myCreateWindow(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (window == NULL) {
		glfwTerminate();
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

	//  ����Shaders
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


	//  ����VAO����VAO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	//  ����VBO����VBO
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	//  ���ƶ������ݵ�������ڴ���
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//  ���Ӷ������Բ�����
	//  λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	//  ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)(9*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	//  ���
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

/*
**********************************************************************
*/
	//  window��GUI
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsClassic();

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

/*
**********************************************************************
*/
	myGUI* mygui = new myGUI();
	//  ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplGlfwGL3_NewFrame();

		//  ����Gui����ʵʱ���¶�������
		{
			mygui->createOptions();
			mygui->updateVertices(vertices);
		}

		glUseProgram(shaderProgram->getShaderProgram());
		//  �󶨻����ڴ�
		//glBindVertexArray(mVAO);
		if (mygui->isChanged()) {
			//glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			mygui->resetChangedFlag();
		}
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//  ����ImGui::Render()������Ⱦ
		ImGui::Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);

	glfwTerminate();

	//  ɾ��new�Ķ���
	delete mygui;
	delete shaderProgram;
	delete fragmentShader;
	delete vertexShader;
	//system("pause");
	return 0;
}


