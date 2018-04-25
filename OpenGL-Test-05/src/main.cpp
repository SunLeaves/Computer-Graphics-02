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


int main() {

	float lightPos[3] = { -1.0f, 1.0f, -1.0f };
	float lightColor[3] = { 1.0f, 1.0f, 1.0f };
	float objColor[3] = { 0.3f, 0.5f, 0.2f };

	float objVertices[36][6] = { 0 };
	float lightVertices[36][3] = { 0 };
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	GLFWwindow* window = NULL;
	myVertexShader* objVertexShader_Phong = NULL;
	myVertexShader* objVertexShader_Gouraud = NULL;
	myFragmentShader* objFragShader_Gouraud = NULL;
	myFragmentShader* objFragShader_Phong = NULL;
	myShaderProgram* objShaderProgram_Phong = NULL;
	myShaderProgram* objShaderProgram_Gouraud = NULL;


	myVertexShader* lightVertexShader = NULL;
	myFragmentShader* lightFragShader = NULL;
	myShaderProgram* lightShaderProgram = NULL;

	unsigned int objVAO = 0;
	unsigned int objVBO = 0;

	unsigned int lightVBO = 0;
	unsigned int lightVAO = 0;

	//  矩阵
	glm::mat4 identity(1);
	glm::mat4 model(1);
	glm::mat4 view(1);
	glm::mat4 projection(1);

	//  设置顶点矩阵
	getObjVertices(objVertices);
	getLightVertices(lightVertices);

	//  创建窗口
	if (!myCreateWindow(window, INIT_WIDTH, INIT_HEIGHT)) {
		return -1;
	}

	/*------------------------Phong Shading----------------------------------*/
	//  此处代码待模块化

	//  创建顶点着色器
	objVertexShader_Phong = new myVertexShader(0);
	//  创建片段着色器
	objFragShader_Phong = new myFragmentShader(0);

	//  创建Shader Program
	objShaderProgram_Phong = new myShaderProgram();
	if (!objShaderProgram_Phong->isSucceed()) {
		cout << "Shader program error." << endl;
		glfwTerminate();
		return -1;
	}

	//  链接着色器
	glAttachShader(objShaderProgram_Phong->getShaderProgram(), objVertexShader_Phong->getVertexShader());
	glAttachShader(objShaderProgram_Phong->getShaderProgram(), objFragShader_Phong->getFragmentShader());
	glLinkProgram(objShaderProgram_Phong->getShaderProgram());
	//  检测链接错误
	if (!objShaderProgram_Phong->shaderProgramTest()) {
		cout << "Shader Program error." << endl;
		glfwTerminate();
		return -1;
	}
	//  删除着色器对象
	objVertexShader_Phong->deleteShader();
	objFragShader_Phong->deleteShader();

	/*------------------------Gouraud着色器--------------------------*/
	//  创建顶点着色器
	objVertexShader_Gouraud = new myVertexShader(1);
	if (!objVertexShader_Gouraud->isSucceed()) {
		glfwTerminate();
		return -1;
	}

	//  创建片段着色器
	objFragShader_Gouraud = new myFragmentShader(1);
	if (!objFragShader_Gouraud->isSucceed()) {
		glfwTerminate();
		return -1;
	}

	//  创建Shader Program
	objShaderProgram_Gouraud = new myShaderProgram();
	if (!objShaderProgram_Gouraud->isSucceed()) {
		cout << "Shader program error." << endl;
		glfwTerminate();
		return -1;
	}

	//  链接着色器
	glAttachShader(objShaderProgram_Gouraud->getShaderProgram(), objVertexShader_Gouraud->getVertexShader());
	glAttachShader(objShaderProgram_Gouraud->getShaderProgram(), objFragShader_Gouraud->getFragmentShader());
	glLinkProgram(objShaderProgram_Gouraud->getShaderProgram());
	//  检测链接错误
	if (!objShaderProgram_Gouraud->shaderProgramTest()) {
		cout << "Shader Program error." << endl;
		glfwTerminate();
		return -1;
	}
	//  删除着色器对象
	objVertexShader_Gouraud->deleteShader();
	objFragShader_Gouraud->deleteShader();

	/*-------------------------------------------------------------*/

	//  生成物体VAO，VBO
	glGenVertexArrays(1, &objVAO);
	glBindVertexArray(objVAO);
	glGenBuffers(1, &objVBO);
	glBindBuffer(GL_ARRAY_BUFFER, objVBO);

	//  复制顶点数据到缓冲内存中，链接顶点属性
	glBufferData(GL_ARRAY_BUFFER, sizeof(objVertices), objVertices, GL_STATIC_DRAW);
	//  位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
	//  颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//  解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*-----------------------Uniform 变量处理--------------------------------------*/

	//  获取uniform变量位置
	int objModelLoc_Phong = glGetUniformLocation(objShaderProgram_Phong->getShaderProgram(), "model"),
		objViewLoc_Phong = glGetUniformLocation(objShaderProgram_Phong->getShaderProgram(), "view"),
		objProjLoc_Phong = glGetUniformLocation(objShaderProgram_Phong->getShaderProgram(), "projection"),
		objColorLoc_Phong = glGetUniformLocation(objShaderProgram_Phong->getShaderProgram(), "objColor"),
		lightColorLoc_Phong = glGetUniformLocation(objShaderProgram_Phong->getShaderProgram(), "lightColor"),
		lightPosLoc_Phong = glGetUniformLocation(objShaderProgram_Phong->getShaderProgram(), "lightPos"),
		viewPosLoc_Phong = glGetUniformLocation(objShaderProgram_Phong->getShaderProgram(), "viewPos");

	float viewPosF[3] = { 2.0f, 2.0f, 2.0f };
	glm::vec3 viewPos = { 2.0f, 2.0f, 2.0f };
	glm::vec3 objCenter = { 0.0f, 0.0f, 0.0f };
	glm::vec3 upVec = { 0.0f, 1.0f, 0.0f };
	//  设置model、view、projection矩阵（初始化）
	view = glm::lookAt(viewPos, objCenter, upVec);
	projection = glm::perspective(glm::radians(50.0f), 1.0f, 0.01f, 100.0f);
	glUseProgram(objShaderProgram_Phong->getShaderProgram());
	glUniformMatrix4fv(objModelLoc_Phong, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(objViewLoc_Phong, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(objProjLoc_Phong, 1, GL_FALSE, &projection[0][0]);
	glUniform3fv(objColorLoc_Phong, 1, objColor);
	glUniform3fv(lightColorLoc_Phong, 1, lightColor);
	glUniform3fv(lightPosLoc_Phong, 1, lightPos);
	glUniform3fv(viewPosLoc_Phong, 1, viewPosF);

	/*----------------------------Uniform变量处理---------------------------------------*/
	int objModelLoc_Gouraud = glGetUniformLocation(objShaderProgram_Gouraud->getShaderProgram(), "model"),
		objViewLoc_Gouraud = glGetUniformLocation(objShaderProgram_Gouraud->getShaderProgram(), "view"),
		objProjLoc_Gouraud = glGetUniformLocation(objShaderProgram_Gouraud->getShaderProgram(), "projection"),
		objColorLoc_Gouraud = glGetUniformLocation(objShaderProgram_Gouraud->getShaderProgram(), "objColor"),
		lightColorLoc_Gouraud = glGetUniformLocation(objShaderProgram_Gouraud->getShaderProgram(), "lightColor"),
		lightPosLoc_Gouraud = glGetUniformLocation(objShaderProgram_Gouraud->getShaderProgram(), "lightPos"),
		viewPosLoc_Gouraud = glGetUniformLocation(objShaderProgram_Gouraud->getShaderProgram(), "viewPos");

	glUseProgram(objShaderProgram_Gouraud->getShaderProgram());
	glUniformMatrix4fv(objModelLoc_Gouraud, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(objViewLoc_Gouraud, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(objProjLoc_Gouraud, 1, GL_FALSE, &projection[0][0]);
	glUniform3fv(objColorLoc_Gouraud, 1, objColor);
	glUniform3fv(lightColorLoc_Gouraud, 1, lightColor);
	glUniform3fv(lightPosLoc_Gouraud, 1, lightPos);
	glUniform3fv(viewPosLoc_Gouraud, 1, viewPosF);

	/*-------------------------------------------------------------------*/

	/*--------------------------光照立方体--------------------------------*/
	//  此处代码待模块化

	//  生成光照立方体的VAO,VBO
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glGenBuffers(1, &lightVBO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);

	//  复制顶点数据到缓冲内存中，链接顶点属性
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
	//  位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	//  启用属性
	glEnableVertexAttribArray(0);
	//  解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	lightVertexShader = new myVertexShader(2);
	lightFragShader = new myFragmentShader(2);
	lightShaderProgram = new myShaderProgram();

	//  创建Shader Program
	lightShaderProgram = new myShaderProgram();
	if (!lightShaderProgram->isSucceed()) {
		cout << "Shader program error." << endl;
		glfwTerminate();
		return -1;
	}

	//  链接着色器
	glAttachShader(lightShaderProgram->getShaderProgram(), lightVertexShader->getVertexShader());
	glAttachShader(lightShaderProgram->getShaderProgram(), lightFragShader->getFragmentShader());
	glLinkProgram(lightShaderProgram->getShaderProgram());
	//  检测链接错误
	if (!lightShaderProgram->shaderProgramTest()) {
		cout << "Shader Program error." << endl;
		glfwTerminate();
		return -1;
	}
	//  删除着色器对象
	lightVertexShader->deleteShader();
	lightFragShader->deleteShader();
	
	//  获取uniform变量位置
	int lightModelLoc = glGetUniformLocation(lightShaderProgram->getShaderProgram(), "model");
	int lightViewLoc = glGetUniformLocation(lightShaderProgram->getShaderProgram(), "view");
	int lightProjLoc = glGetUniformLocation(lightShaderProgram->getShaderProgram(), "projection");

	glm::mat4 lightModel = glm::translate(identity, glm::vec3(lightPos[0], lightPos[1], lightPos[2]));
	//  设置model、view、projection矩阵（初始化）
	glUseProgram(lightShaderProgram->getShaderProgram());
	glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, &lightModel[0][0]);
	glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(lightProjLoc, 1, GL_FALSE, &projection[0][0]);


	/*----------------------------------------------------------*/

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//  物体部分
		glBindBuffer(GL_ARRAY_BUFFER, objVBO);
		glBindVertexArray(objVAO);
		glUseProgram(objShaderProgram_Gouraud->getShaderProgram());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//  光源立方体
		glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
		glBindVertexArray(lightVAO);
		glUseProgram(lightShaderProgram->getShaderProgram());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ImGui::Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//  解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &objVAO);
	glDeleteBuffers(1, &objVBO);
	glfwTerminate();

	delete objShaderProgram_Phong;
	delete objFragShader_Phong;
	delete objVertexShader_Phong;
	//delete mygui;
	system("pause");
	return 0;
}

