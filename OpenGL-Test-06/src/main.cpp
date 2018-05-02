#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>


#include "MyWindow.h"
#include "Shader.h"
#include "MyVertices.h"

#define INIT_HEIGHT 900
#define INIT_WIDTH 900

using namespace std;

template<size_t M, size_t N>
void createVBO_VAO(unsigned int& VBO, unsigned int& VAO, const float(&vertices)[M][N], string type);

void setUniforms(Shader& shader,
	const glm::mat4(&model),
	const glm::mat4(&view),
	const glm::mat4(&projection));

void setUniforms(Shader& shader,
	const glm::mat4(&model),
	const glm::mat4(&view),
	const glm::mat4(&projection),
	const glm::vec3(&cubeColor),
	const glm::vec3(&lightColor),
	const glm::vec3(&lightPos),
	const glm::vec3(&viewPos));

void setFactors(Shader& shader, float ambient, float diffuse, float specular, int shininess);

void createGUI(int& projMethod, float& aBias, float& bBias);


int main() {
	GLFWwindow* window = NULL;

	//  着色器路径
	string cubeVertexShaderPath = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-06/shader/ObjVertexPhongShader.vs";
	string cubeFragShaderPath = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-06/shader/ObjFragPhongShader.fs";

	string planeVertexShaderPath = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-06/shader/ObjVertexPhongShader.vs";
	string planeFragShaderPath = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-06/shader/ObjFragPhongShader.fs";

	string quadVertexShaderPath = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-06/shader/QuadVertexShader.vs";
	string quadFragShaderPath = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-06/shader/QuadFragShader.fs";

	string depthVertexShaderPath = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-06/shader/SimpleDepthShader.vs";
	string depthFragShaderPath = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-06/shader/SimpleDepthShader.fs";


	//  VBO、VAO
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;
	unsigned int planeVAO = 0;
	unsigned int planeVBO = 0;
	unsigned int quadVAO = 0;
	unsigned int quadVBO = 0;

	//  矩阵
	glm::mat4 identity(1);
	glm::mat4 cubeModel(1);
	glm::mat4 planeModel(1);
	glm::mat4 lightModel(1);
	glm::mat4 view(1);
	glm::mat4 projection(1);

	//  视角，上向量
	glm::vec3 viewPos = {0.0f, 1.5f, 3.0f };
	glm::vec3 upVec = { 0.0f, 1.0f, 0.0f };

	//  光源位置、颜色、（立方体）顶点位置信息
	glm::vec3 lightPos = { -2.0f, 3.0f, -2.0f };
	glm::vec3 lightColor = { 1.0f, 1.0f, 1.0f };
	//float lightVertices[36][3] = { 0 };

	//  物体、平面的颜色、顶点位置信息
	glm::vec3 cubeCenter = { 0.0f, 0.6f, 0.0f };
	glm::vec3 cubeColor = { 0.1f, 0.1f, 0.5f };
	glm::vec3 planePos = { 0.0f, 0.3f, 0.0f };
	glm::vec3 planeColor = { 0.82f, 0.41f, 0.12f };
	float cubeVertices[36][6] = { 0 };
	float planeVertices[6][6] = { 0 };
	float quadVertices[4][5] = { 0 };

	//  背景颜色
	float clearColor[4] = { 0.5f, 0.5f, 0.5f, 0.5f };

	//  光照参数因子
	float ambientFactor = 0.2f,
		diffuseFactor = 1.0f,
		specularFactor = 0.5f;
	int shininess = 128;

	float planeAmbientFactor = 0.1f,
		planeDiffuseFactor = 0.5f,
		planeSpecularFactor = 0.3f;
	int planeShininess = 64;

	//  阴影Bias
	float orthBias = 0.001,
		perspBias = 0.00003,
		bias = orthBias;


	/*-------------------------初始化-----------------------*/

	//  初始化顶点矩阵
	setObjVertices(cubeVertices);
	setPlaneVertices(planeVertices);
	setQuadVertices(quadVertices);

	//  初始化光位置透视矩阵、正交矩阵、视角、远近平面
	GLfloat nearPlane = 0.01f, farPlane = 75.0f;
	glm::mat4 lightProjectionOrth = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane),
		lightProjectionPersp = glm::perspective(glm::radians(45.0f), 1.0f, nearPlane, farPlane),
		lightView = glm::lookAt(lightPos, cubeCenter, upVec),
		lightSpaceMatrixOrth = lightProjectionOrth * lightView,
		lightSpaceMatrixPersp = lightProjectionPersp * lightView,
		usedLightSpaceMatrix = lightSpaceMatrixOrth;

	//  设置model、view、projection矩阵（初始化）
	cubeModel = glm::translate(identity, cubeCenter);
	cubeModel = glm::rotate(cubeModel, glm::radians(30.0f), upVec);
	planeModel = glm::translate(identity, planePos);
	lightModel = glm::translate(identity, lightPos);
	view = glm::lookAt(viewPos, cubeCenter, upVec);
	lightView = glm::lookAt(lightPos, cubeCenter, upVec);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 100.0f);

	//  创建窗口
	if (!myCreateWindow(window, "HW7", INIT_WIDTH, INIT_HEIGHT)) {
		return -1;
	}


	/*------------------------------------------------------*/

	//  深度贴图帧缓冲对象
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	//  创建2D纹理
	const GLuint SHADOW_WIDTH = 900, SHADOW_HEIGHT = 900;
	GLuint depthMap = 0;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, INIT_WIDTH, INIT_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[4] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// 将生成的深度纹理作为帧缓冲的深度贴图 
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/*----------------------物体着色器程序-------------------*/

	//  物体着色器程序
	Shader cubeProgram(cubeVertexShaderPath.c_str(), cubeFragShaderPath.c_str(), nullptr);
	//  生成物体VBO，VAO
	createVBO_VAO(cubeVBO, cubeVAO, cubeVertices, "cube");

	//  平面着色器程序
	Shader planeProgram(planeVertexShaderPath.c_str(), planeFragShaderPath.c_str(), nullptr);
	//  生成平面VBO，VAO
	createVBO_VAO(planeVBO, planeVAO, planeVertices, "plane");

	//  屏幕四边形
	Shader quadProgram(quadVertexShaderPath.c_str(), quadFragShaderPath.c_str(), nullptr);
	createVBO_VAO(quadVBO, quadVAO, quadVertices, "quad");

	// simpleDepthShader
	Shader simpleDepthShader(depthVertexShaderPath.c_str(), depthFragShaderPath.c_str(), nullptr);

	/*-----------------------Uniform 变量-------------------*/

	// 物体
	cubeProgram.use();
	cubeProgram.setMat4("lightSpaceMatrix", usedLightSpaceMatrix);
	setUniforms(cubeProgram, cubeModel, view, projection, cubeColor, lightColor, lightPos, viewPos);
	setFactors(cubeProgram, ambientFactor, diffuseFactor, specularFactor, shininess);
	//setUniforms(cubeProgram, cubeModel, lightView, projection, cubeColor, lightColor, lightPos, lightPos);
	//setFactors(cubeProgram, ambientFactor, diffuseFactor, specularFactor, shininess);

	// 平面
	planeProgram.use();
	planeProgram.setMat4("lightSpaceMatrix", usedLightSpaceMatrix);
	setUniforms(planeProgram, planeModel, view, projection, planeColor, lightColor, lightPos, viewPos);
	setFactors(planeProgram, planeAmbientFactor, planeDiffuseFactor, planeSpecularFactor, planeShininess);
	//setUniforms(planeProgram, planeModel, lightView, projection, planeColor, lightColor, lightPos, lightPos);
	//setFactors(planeProgram, ambientFactor, diffuseFactor, specularFactor, shininess);

	//  quad
	quadProgram.use();
	quadProgram.setInt("depthMap", 0);
	quadProgram.setFloat("near_plane", nearPlane);
	quadProgram.setFloat("far_plane", farPlane);

	//  simpleDepthShader
	simpleDepthShader.use();
	simpleDepthShader.setMat4("lightSpaceMatrix", usedLightSpaceMatrix);
	simpleDepthShader.setMat4("model", cubeModel);

	/*-------------------------渲染-------------------------*/

	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsClassic();

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

	int projMethod = 0;

	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);

		ImGui_ImplGlfwGL3_NewFrame();

		createGUI(projMethod, orthBias, perspBias);
		usedLightSpaceMatrix = (projMethod == 0) ? lightSpaceMatrixOrth : lightSpaceMatrixPersp;
		bias = (projMethod == 0) ? orthBias : perspBias;
		
		/*-----------------使用深度缓冲渲染------------------*/
		glViewport(0, 0, INIT_WIDTH, INIT_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		simpleDepthShader.use();
		
		//  平面部分
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBindVertexArray(planeVAO);
		simpleDepthShader.setMat4("lightSpaceMatrix", usedLightSpaceMatrix);
		simpleDepthShader.setMat4("model", planeModel);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//  物体部分
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBindVertexArray(cubeVAO);
		simpleDepthShader.setMat4("lightSpaceMatrix", usedLightSpaceMatrix);
		simpleDepthShader.setMat4("model", cubeModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		
		/*-----------------以默认帧缓冲渲染----------------------------*/

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, INIT_WIDTH, INIT_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

		//  物体部分
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBindVertexArray(cubeVAO);
		cubeProgram.use();
		cubeProgram.setFloat("bias", bias);
		cubeProgram.setMat4("lightSpaceMatrix", usedLightSpaceMatrix);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//  平面部分
		glBindVertexArray(planeVAO);
		planeProgram.use();
		planeProgram.setFloat("bias", bias);
		planeProgram.setMat4("lightSpaceMatrix", usedLightSpaceMatrix);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		/*--------------屏幕四边形显示深度贴图-----------------*/

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glViewport(0, 0, INIT_WIDTH, INIT_HEIGHT);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//quadProgram.use();
		//quadProgram.setFloat("near_plane", nearPlane);
		//quadProgram.setFloat("far_plane", farPlane);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, depthMap);
		//glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		//glBindVertexArray(quadVAO);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		
		ImGui::Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


template<size_t M, size_t N>
void createVBO_VAO(unsigned int& VBO, unsigned int& VAO, const float(&vertices)[M][N], string type) {
	//  生成物体VAO，VBO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	if (type == "cube" || type == "plane") {
		//  复制顶点数据到缓冲内存中，链接顶点属性
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//  位置属性
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);
		//  法向量属性
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);
	}
	else if (type == "light") {
		//  复制顶点数据到缓冲内存中，链接顶点属性
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//  位置属性
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);
	}
	else if (type == "quad") {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	else  {
		cout << "ERROR::TYPE IS NOT \"cubeect\" OR \"light\"." << endl;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void setUniforms(Shader& shader,
	const glm::mat4(&model),
	const glm::mat4(&view),
	const glm::mat4(&projection)) {
	shader.use();
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
}

void setUniforms(Shader& shader,
	const glm::mat4(&model),
	const glm::mat4(&view),
	const glm::mat4(&projection),
	const glm::vec3(&objColor),
	const glm::vec3(&lightColor),
	const glm::vec3(&lightPos),
	const glm::vec3(&viewPos)) {
	shader.use();
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	shader.setVec3("objColor", objColor);
	shader.setVec3("lightColor", lightColor);
	shader.setVec3("lightPos", lightPos);
	shader.setVec3("viewPos", viewPos);
}

void setFactors(Shader& shader, float ambient, float diffuse, float specular, int shininess) {
	shader.use();
	shader.setFloat("ambientFactor", ambient);
	shader.setFloat("diffuseFactor", diffuse);
	shader.setFloat("specularFactor", specular);
	shader.setInt("shininess", shininess);
}


void createGUI(int& projMethod, float& orthBias, float& perspBias) {
	ImGui::RadioButton("Orth", &projMethod, 0);

	ImGui::RadioButton("Persp", &projMethod, 1);

	ImGui::SliderFloat("orthBias", &orthBias, 0.00001, 0.01, "%.6f");
	ImGui::SliderFloat("perspBias", &perspBias, 0.00001, 0.01, "%.6f");
}


