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

	// ����
	glm::mat4 scale;
	glm::mat4 trans;
	glm::mat4 rotate;
	glm::mat4 identity;
	rotate = glm::rotate(rotate, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 1.0f));

	//  ���ö������
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
	if (!fragmentShader->isSucceed()) {
		glfwTerminate();
		return -1;
	}

	//  ����Shader Program
	shaderProgram = new myShaderProgram();
	if (!shaderProgram->isSucceed()) {
		cout << "Shader program error." << endl;
		glfwTerminate();
		return -1;
	}

	//  ������ɫ��
	glAttachShader(shaderProgram->getShaderProgram(), vertexShader->getVertexShader());
	glAttachShader(shaderProgram->getShaderProgram(), fragmentShader->getFragmentShader());
	glLinkProgram(shaderProgram->getShaderProgram());
	//  ������Ӵ���
	if (!shaderProgram->shaderProgramTest()) {
		cout << "Shader Program error." << endl;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//  λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
	//  ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//  ��ȡuniformλ��
	int scaleLoc = glGetUniformLocation(shaderProgram->getShaderProgram(), "scale"),
		transLoc = glGetUniformLocation(shaderProgram->getShaderProgram(), "trans"),
		rotateLoc = glGetUniformLocation(shaderProgram->getShaderProgram(), "rotate");

	//  ����uniformֵ
	glUseProgram(shaderProgram->getShaderProgram());
	glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, &scale[0][0]);
	glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, &rotate[0][0]);
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, &trans[0][0]);

	//  ��GUI��window����
	mygui = new myGUI();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsClassic();

	//  ������Ȳ���
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	float nowTime = 0.0f, rest = 0.0f;

	//  ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//  ����GUI����
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

	//  ���
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