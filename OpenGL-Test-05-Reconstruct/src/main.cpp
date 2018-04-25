#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>

#include "MyWindow.h"
#include "MyVertices.h"
#include "Shader.h"

#define INIT_WIDTH 900
#define INIT_HEIGHT 900

using namespace std;

template<size_t M, size_t N>
void createVBO_VAO(unsigned int& VBO, unsigned int& VAO, const float(&vertices)[M][N], string type);

void setUniforms(Shader& shader,
	const glm::mat4(&model),
	const glm::mat4(&view),
	const glm::mat4(&projection));

void setUniforms(Shader& shader, 
	const glm::mat4 (&model), 
	const glm::mat4 (&view), 
	const glm::mat4 (&projection), 
	const glm::vec3 (&objColor), 
	const glm::vec3 (&lightColor), 
	const glm::vec3 (&lightPos), 
	const glm::vec3 (&viewPos));

void setFactors(Shader& shader, float ambient, float diffuse, float specular, int shininess);

void createGUI(int& shadingMethod, float& ambient, float& diffuse, float& specular, int& shininess);

void rotate(glm::mat4& matrix);

int main() {
	GLFWwindow* window = NULL;

	//  物体着色器源代码路径
	string objVertexShader_Phong = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-05-Reconstruct/src/shader/ObjVertexPhongShader.vs";
	string objVertexShader_Gouraud = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-05-Reconstruct/src/shader/ObjVertexGouraudShader.vs";
	string objFragShader_Phong = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-05-Reconstruct/src/shader/ObjFragPhongShader.fs";
	string objFragShader_Gouraud = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-05-Reconstruct/src/shader/ObjFragGouraudShader.fs";

	//  光源立方体着色器源代码路径
	string lightVertexShader = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-05-Reconstruct/src/shader/LightVertexShader.vs";
	string lightFragShader = "D:/Projects/VS-Projects/Computer-Graphics-02/OpenGL-Test-05-Reconstruct/src/shader/LightFragShader.fs";

	//  VBO、VAO
	unsigned int objVAO = 0;
	unsigned int objVBO = 0;
	unsigned int lightVAO = 0;
	unsigned int lightVBO = 0;

	//  矩阵
	glm::mat4 identity(1);
	glm::mat4 objModel(1);
	glm::mat4 lightModel(1);
	glm::mat4 view(1);
	glm::mat4 projection(1);

	//  视角，物体中心，上向量
	glm::vec3 viewPos = { 2.0f, 2.0f, 2.0f };
	glm::vec3 objCenter = { 0.0f, 0.0f, 0.0f };
	glm::vec3 upVec = { 0.0f, 1.0f, 0.0f };

	//  光源位置、颜色、（立方体）顶点信息
	glm::vec3 lightPos = { -1.0f, 1.0f, -1.0f };
	glm::vec3 lightColor = { 1.0f, 1.0f, 1.0f };
	float lightVertices[36][3] = { 0 };

	//  物体颜色、顶点信息
	glm::vec3 objColor = { 0.1f, 0.1f, 0.5f };
	float objVertices[36][6] = { 0 };

	//  背景颜色
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	//  GUI控件数据
	int shadingMethod = 0;
	float ambientFactor = 0.1f;
	float diffuseFactor = 1.0f;
	float specularFactor = 0.5f;
	int shininess = 128;

	/*------------------------初始化------------------------*/

	//  初始化顶点矩阵
	setObjVertices(objVertices);
	setLightVertices(lightVertices);

	//  设置model、view、projection矩阵（初始化）
	lightModel = glm::translate(identity, lightPos);
	view = glm::lookAt(viewPos, objCenter, upVec);
	projection = glm::perspective(glm::radians(20.0f), 1.0f, 0.01f, 100.0f);

	//  创建窗口
	if (!myCreateWindow(window, INIT_WIDTH, INIT_HEIGHT)) {
		return -1;
	}


	/*--------------------物体着色器程序----------------------*/

	//  物体着色器程序
	//  物体Phong着色器程序
	Shader objProgram_Phong(objVertexShader_Phong.c_str(), objFragShader_Phong.c_str(), nullptr);
	//  物体Gouraud着色器程序
	Shader objProgram_Gouraud(objVertexShader_Gouraud.c_str(), objFragShader_Gouraud.c_str(), nullptr);

	//  生成物体VBO，VAO
	createVBO_VAO(objVBO, objVAO, objVertices, "object");


	/*------------------光源立方体着色器程序------------------*/

	//  光源立方体着色器程序
	Shader lightProgram(lightVertexShader.c_str(), lightFragShader.c_str(), nullptr);
	
	//  生成光源立方体VBO, VAO
	createVBO_VAO(lightVBO, lightVAO, lightVertices, "light");

	/*-------------------------渲染-------------------------*/

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsClassic();

	while (!glfwWindowShouldClose(window)) {
		myProcessInput(window);
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplGlfwGL3_NewFrame();
		createGUI(shadingMethod, ambientFactor, diffuseFactor, specularFactor, shininess);

		//  物体部分
		glBindBuffer(GL_ARRAY_BUFFER, objVBO);
		glBindVertexArray(objVAO);
		if (shadingMethod == 0) {
			rotate(objModel);
			setUniforms(objProgram_Phong, objModel, view, projection, objColor, lightColor, lightPos, viewPos);
			setUniforms(lightProgram, lightModel, view, projection);
			setFactors(objProgram_Phong, ambientFactor, diffuseFactor, specularFactor, shininess);
			objProgram_Phong.use();
		} else {
			rotate(objModel);
			setUniforms(objProgram_Gouraud, objModel, view, projection, objColor, lightColor, lightPos, viewPos);
			setUniforms(lightProgram, lightModel, view, projection);
			setFactors(objProgram_Gouraud, ambientFactor, diffuseFactor, specularFactor, shininess);
			objProgram_Gouraud.use();
		}

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//  光源立方体
		glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
		glBindVertexArray(lightVAO);
		lightProgram.use();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		ImGui::Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//  解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &objVAO);
	glDeleteBuffers(1, &objVBO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightVBO);
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

	if (type == "object") {
		//  复制顶点数据到缓冲内存中，链接顶点属性
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//  位置属性
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);
		//  颜色属性
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
	else {
		cout << "ERROR::TYPE IS NOT \"object\" OR \"light\"." << endl;
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


void createGUI(int& shadingMethod, float& ambient, float& diffuse, float& specular, int& shininess) {
	ImGui::RadioButton("Phong Shading", &shadingMethod, 0);
	ImGui::RadioButton("Gouraud Shading", &shadingMethod, 1);

	ImGui::SliderFloat("Ambient", &ambient, 0.0f, 10.0f);
	ImGui::SliderFloat("Diffuse", &diffuse, 0.0f, 10.0f);
	ImGui::SliderFloat("Specular", &specular, 0.0f, 10.0f);

	ImGui::SliderInt("Shininess", &shininess, 2, 256);
}


void rotate(glm::mat4& matrix) {
	matrix = glm::rotate(matrix, glm::radians(0.01f), glm::vec3(0.0f, 1.0f, 0.0f));
}